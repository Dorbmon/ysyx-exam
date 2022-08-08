#include <memory>
#include <nvboard.h>
#include <Vysyx_22041207_top.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "diff.h"
#include "memory.h"
#include "Vysyx_22041207_top__Dpi.h"
#include "verilated_dpi.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "isa.h"
#include "itrace.h"
#include "expr.h"
#include "elf.h"
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
double sc_time_stamp() { return 0; }
const std::unique_ptr<VerilatedContext> contextp = std::make_unique<VerilatedContext>();
Vysyx_22041207_top* top = new Vysyx_22041207_top{contextp.get(), "TOP"};
void nvboard_bind_all_pins(Vysyx_22041207_top* top);
bool sebreak = false;
void ebreak() {
  sebreak = true;
}
char* img_file = NULL;

extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu.gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}
static void runN(uint64_t n) {
  static uint64_t count = 0;
  n <<= 1;
  while (!contextp->gotFinish() && !sebreak /*&& count < n*/) {
    count ++;
    
    top->clk = ~top->clk;
    uint32_t bpc = top->pc;
    if (count & 1) {
      printf("pc:%lx\n", top->pc);
      //pBin(pmem_read(top->pc, 4));
      loadINST(pmem_read(top->pc, 4), top->pc);
    }
    cpu.pc = top->pc;
    top->eval();
    if (top->clk) { //上升沿才会计算 如果top->clk = true 说明刚刚是一个上升沿，已经完成了一次计算
      //printf("difftest pc:%lx\n", bpc);
      difftest_step(bpc, top->pc);
    }
  }
}
static int simulate(char *args) {
  uint64_t N = 1;
  if (args != NULL) {
    N = atoi(args);
  }
  runN(N);
  if (sebreak) {
    if (cpu.gpr [10] == 0) {
      printf("HIT GOOD TRAP.\n");
    } else {
      printf("HIT BAD TRAP. code is %lx\n", cpu.gpr [10]);
      return cpu.gpr [10];
    }
  }
  return 0;
}
static int readMemory(char *args) {
  char *c_byteNum = strtok(args, " ");
  char *c_address = args + strlen(c_byteNum) + 1;
  bool success = true;
  paddr_t address = expr(c_address, &success);
  if (!success) {
    return -1;
  }
  // sscanf(c_address ,"%x", &address);
  int byteNum = atoi(c_byteNum);
  for (uint64_t i = 0; i < byteNum; ++i) {
    printf("0x%lx 0x%lx\n", address + i * 4, pmem_read(address + i * 4, 4));
  }
  return 0;
}
static struct {
  const char *name;
  const char *description;
  int (*handler)(char *);
} cmd_table[] = {
    {"si", "Run N lines of code", simulate},
    {"x", "Read Memory", readMemory},
};

#define NR_CMD ARRLEN(cmd_table)
static char *rl_gets() {
  static char *line_read = NULL;
  if (line_read) {
    free(line_read);
    line_read = NULL;
  }
  line_read = readline("(npc) ");
  if (line_read && *line_read) {
    add_history(line_read);
  }
  return line_read;
}
bool batchMode = false;
static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"elf"      , required_argument, NULL, 'e'},
    {"img"      , required_argument, NULL, 'i'},
    {"diff"     , required_argument, NULL, 'd'},
    {"batch"    , no_argument, NULL, 'b'},
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "bi:e:d:", table, NULL)) != -1) {
    switch (o) {
      case 'e': elf_file = optarg; break;
      case 'i': img_file = optarg;break;
      case 'd': diff_so = optarg;break;
      case 'b': batchMode = true;break;
      //case 1: img_file = optarg; return 0;
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
int main(int argc, char **argv, char **env) {
  parse_args(argc, argv);
  //nvboard_bind_all_pins(top);
  //nvboard_init();
  init_regex();
  init_disasm("riscv64");
  initMemory(img_file); // 会自动加载程序
  //init_elf();
  initDiffset();
  contextp->traceEverOn(true);
  contextp->commandArgs(argc, argv);
  VerilatedVcdC *vcd = new VerilatedVcdC();
  top->trace(vcd, 0);
  vcd->open("data.vcd");
  top->clk = 0;
  top->eval();
  if (batchMode) {
    simulate("1000000");
    return 0;
  }
  for (char *str; (str = rl_gets()) != NULL;) {
    char *str_end = str + strlen(str);
    char *cmd = strtok(str, " ");
    if (cmd == NULL) {
      continue;
    }
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

    int i;
    for (i = 0; i < NR_CMD; i++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        int res = cmd_table[i].handler(args);
        if (res < 0) {
          return res;
        }
        break;
      }
    }

    if (i == NR_CMD) {
      printf("Unknown command '%s'\n", cmd);
    }
  }
  top->final();
  vcd->close();
  return 0;
}
