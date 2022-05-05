#include <stdio.h>
#include "debug.h"
#include <elf.h>
static FILE *elf_fp = NULL;
static size_t funcNum = 0;
static char *elf_file = NULL;
static struct func {
  char funcName[20];
  uint64_t address, size;
} funcs[5000];
static char* getBelongFunction(uint64_t addr) {
  for (int i = 0;i < funcNum - 1;++ i) {
    if (addr >= funcs[i].address && addr < funcs[i + 1].address) return funcs[i].funcName;
  }
  return funcs[funcNum - 1].funcName;
}
static int comp(const void*a, const void*b) {
  return ((struct func*)a)->address - ((struct func*)b)->address;
}
static void init_elf() {
  if (elf_file == NULL) return ;
  elf_fp = fopen(elf_file, "r");
  Elf64_Ehdr elf_head;
	int a;
	a = fread(&elf_head, sizeof(Elf64_Ehdr), 1, elf_fp); 
  if (0 == a) {
		printf("fail to read head\n");
		assert(0);
	}

	// 判断elf文件类型
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

	// 读取内容
	a = fread(shstrtab, shdr[elf_head.e_shstrndx].sh_size, 1, elf_fp);
	if (0 == a) {
		printf("\nfaile to read\n");
    assert(0);
	}
  char* textTab = NULL;
  for (int i = 0; i < elf_head.e_shnum; i++) {
    temp = shstrtab + shdr[i].sh_name;
    if (strcmp(temp, ".strtab") != 0) continue;//该section名称
    textTab = (char *)malloc(sizeof(uint8_t) * shdr[i].sh_size);
    fseek(elf_fp, shdr[i].sh_offset, SEEK_SET);
    a = fread(textTab, shdr[i].sh_size, 1, elf_fp);
    if (0 == a) {
		  printf("faile to read\n");
      assert(0);
	  }
  }
	// 遍历
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