#include <isa.h>
#include <memory/paddr.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory/vaddr.h>
void init_rand();
void init_log(const char *log_file);
void init_mem();
void init_difftest(char *ref_so_file, long img_size, int port);
void init_device();
void init_sdb();
void init_disasm(const char *triple);
void init_elf();
static void welcome() {
  Log("Trace: %s", MUXDEF(CONFIG_TRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
  IFDEF(CONFIG_TRACE, Log("If trace is enabled, a log file will be generated "
        "to record the trace. This may lead to a large log file. "
        "If it is not necessary, you can disable it in menuconfig"));
  Log("Build time: %s, %s", __TIME__, __DATE__);
  printf("Welcome to %s-NEMU!\n", ANSI_FMT(str(__GUEST_ISA__), ANSI_FG_YELLOW ANSI_BG_RED));
  printf("For help, type \"help\"\n");
}

#ifndef CONFIG_TARGET_AM
#include <getopt.h>

void sdb_set_batch_mode();

static char *log_file = NULL;
static char *diff_so_file = NULL;
static char *img_file = NULL;
static int difftest_port = 1234;
static char *elf_file = NULL;
#define kDisplayWidth 32
static void pBin(long int x)
{
 char s[kDisplayWidth+1];
 int  i=kDisplayWidth;
 s[i--]=0x00;
 do
 {
  s[i--]=(x & 1) ? '1':'0';
  x>>=1;
 } while( x > 0);
 while(i>=0) s[i--]='0';
 printf("%s\n",s);
 return ;
}
static long load_img() {
  if (img_file == NULL) {
    Log("No image is given. Use the default build-in image.");
    return 4096; // built-in image size
  }
  printf("load img file:%s\n", img_file);
  FILE *fp = fopen(img_file, "rb");
  Assert(fp, "Can not open '%s'", img_file);

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  Log("The image is %s, size = %ld", img_file, size);

  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);
  pBin(vaddr_read(0x80000000, 4));
  fclose(fp);
  return size;
}

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"batch"    , no_argument      , NULL, 'b'},
    {"log"      , required_argument, NULL, 'l'},
    {"diff"     , required_argument, NULL, 'd'},
    {"port"     , required_argument, NULL, 'p'},
    {"elf"      , required_argument, NULL, 'e'},
    {"help"     , no_argument      , NULL, 'h'},
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-bhl:d:p:e:", table, NULL)) != -1) {
    switch (o) {
      case 'b': sdb_set_batch_mode(); break;
      case 'p': sscanf(optarg, "%d", &difftest_port); break;
      case 'l': log_file = optarg; break;
      case 'd': diff_so_file = optarg; break;
      case 'e': elf_file = optarg; break;
      case 1: img_file = optarg; return 0;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-b,--batch              run with batch mode\n");
        printf("\t-l,--log=FILE           output log to FILE\n");
        printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
        printf("\n");
        exit(0);
    }
  }
  return 0;
}

void init_monitor(int argc, char *argv[]) {
  /* Perform some global initialization. */

  /* Parse arguments. */
  parse_args(argc, argv);

  /* Set random seed. */
  init_rand();

  /* Open the log file. */
  init_log(log_file);
  init_elf();
  /* Initialize memory. */
  init_mem();

  /* Initialize devices. */
  IFDEF(CONFIG_DEVICE, init_device());

  /* Perform ISA dependent initialization. */
  init_isa();

  /* Load the image to memory. This will overwrite the built-in image. */
  long img_size = load_img();

  /* Initialize differential testing. */
  init_difftest(diff_so_file, img_size, difftest_port);

  /* Initialize the simple debugger. */
  init_sdb();

  IFDEF(CONFIG_ITRACE, init_disasm(
    MUXDEF(CONFIG_ISA_x86,     "i686",
    MUXDEF(CONFIG_ISA_mips32,  "mipsel",
    MUXDEF(CONFIG_ISA_riscv32, "riscv32",
    MUXDEF(CONFIG_ISA_riscv64, "riscv64", "bad")))) "-pc-linux-gnu"
  ));

  /* Display welcome message. */
  welcome();
}
#else // CONFIG_TARGET_AM
static long load_img() {
  extern char bin_start, bin_end;
  size_t size = &bin_end - &bin_start;
  Log("img size = %ld", size);
  memcpy(guest_to_host(RESET_VECTOR), &bin_start, size);
  return size;
}

void am_init_monitor() {
  init_rand();
  init_mem();
  init_isa();
  load_img();
  IFDEF(CONFIG_DEVICE, init_device());
  welcome();
}
#endif
FILE *elf_fp = NULL;
size_t funcNum = 0;
struct func {
  char* funcName;
  uint64_t address, size;
} funcs[5000];
char* getBelongFunction(uint64_t addr) {
  for (int i = 0;i < funcNum - 1;++ i) {
    if (addr >= funcs[i].address && addr < funcs[i + 1].address) return funcs[i].funcName;
  }
  return funcs[funcNum - 1].funcName;
}
int comp(const void*a, const void*b) {
  return ((struct func*)a)->address - ((struct func*)b)->address;
}
void init_elf() {
  if (elf_file == NULL) return ;
  elf_fp = fopen(elf_file, "r");
  Elf64_Ehdr elf_head;
	int a;
	a = fread(&elf_head, sizeof(Elf64_Ehdr), 1, elf_fp); 
  if (0 == a) {
		printf("fail to read head\n");
		assert(0);
	}

	// ??????elf????????????
	if (elf_head.e_ident[0] != 0x7F ||
		elf_head.e_ident[1] != 'E' ||
		elf_head.e_ident[2] != 'L' ||
		elf_head.e_ident[3] != 'F') {
		printf("Not a ELF file\n");
		assert(0);
	}
	Elf64_Shdr *shdr = (Elf64_Shdr*)malloc(sizeof(Elf64_Shdr) * elf_head.e_shnum);
	if (NULL == shdr) {
		printf("shdr malloc failed\n");
		assert(0);
	}
	a = fseek(elf_fp, elf_head.e_shoff, SEEK_SET);
	if (0 != a)
	{
		printf("\nfaile to fseek\n");
		exit(0);
	}
	a = fread(shdr, sizeof(Elf64_Shdr) * elf_head.e_shnum, 1, elf_fp);
	if (0 == a) {
		printf("\nfail to read section\n");
		exit(0);
	}
	rewind(elf_fp);
	fseek(elf_fp, shdr[elf_head.e_shstrndx].sh_offset, SEEK_SET);
	char shstrtab[shdr[elf_head.e_shstrndx].sh_size];
	char *temp = shstrtab;

	// ????????????
	a = fread(shstrtab, shdr[elf_head.e_shstrndx].sh_size, 1, elf_fp);
	if (0 == a) {
		printf("\nfaile to read\n");
    assert(0);
	}
  char* textTab = NULL;
  for (int i = 0; i < elf_head.e_shnum; i++) {
    temp = shstrtab + shdr[i].sh_name;
    if (strcmp(temp, ".strtab") != 0) continue;//???section??????
    textTab = malloc(sizeof(uint8_t) * shdr[i].sh_size);
    fseek(elf_fp, shdr[i].sh_offset, SEEK_SET);
    a = fread(textTab, shdr[i].sh_size, 1, elf_fp);
    if (0 == a) {
		  printf("faile to read\n");
      assert(0);
	  }
  }
	// ??????
	for (int i = 0; i < elf_head.e_shnum; i++)
	{
		temp = shstrtab + shdr[i].sh_name;
    if (strcmp(temp, ".symtab") != 0) continue;
    Elf64_Sym* pSymMem = NULL;
    uint8_t *sign_data=(uint8_t*)malloc(sizeof(uint8_t)*shdr[i].sh_size);
		fseek(elf_fp, shdr[i].sh_offset, SEEK_SET);
		assert(fread(sign_data, sizeof(uint8_t)*shdr[i].sh_size, 1, elf_fp) <= sizeof(uint8_t)*shdr[i].sh_size);
    pSymMem = (Elf64_Sym*)sign_data;
    size_t size = shdr[i].sh_size / shdr[i].sh_entsize;
    for (int k = 0;k < size;++ k) {
      if (ELF64_ST_TYPE(pSymMem[k].st_info) == STT_FUNC) {
        //printf("name:%s\n", textTab + pSymMem[k].st_name);
        funcs[funcNum].funcName = (char*) malloc(strlen(textTab + pSymMem[k].st_name) + 1);
        strcpy(funcs[funcNum].funcName, textTab + pSymMem[k].st_name);
        funcs[funcNum].address = pSymMem[k].st_value;
        funcs[funcNum].size = pSymMem[k].st_size;
        funcNum ++;
      }
    }
    free(sign_data);
	 }
   free(shdr);
   free(textTab);
   qsort(funcs, funcNum, sizeof(struct func), comp);
}