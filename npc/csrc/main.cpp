#include <memory>
#include <nvboard.h>
#include <Vysyx_22041207_top.h>
#include <sys/types.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>
#include "memory.h"
#include "svdpi.h"
#include "Vysyx_22041207_top__Dpi.h"
#include "verilated_dpi.h"
#include <readline/history.h>
#include <readline/readline.h>
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
double sc_time_stamp() { return 0; }
const std::unique_ptr<VerilatedContext> contextp = std::make_unique<VerilatedContext>();
Vysyx_22041207_top* top = new Vysyx_22041207_top{contextp.get(), "TOP"};
void nvboard_bind_all_pins(Vysyx_22041207_top* top);
bool sebreak = false;
void ebreak() {
  sebreak = true;
}
uint64_t *cpu_gpr = NULL;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu_gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}
static void runN(uint64_t n) {
  uint64_t count = 0;
  n <<= 1;
  while (!contextp->gotFinish() && !sebreak && count < n) {
    //contextp->timeInc(1);
    //vcd->dump(time);
    count ++;
    if (count & 1) {
      printf("pc:%lx\n", top->pc);
    }
    top->clk = ~top->clk;
    top->inst = pmem_read(top->pc, 4);
    //std::cout << "Here" << std::endl;
    top->eval();
  }
}
static int simulate(char *args) {
  uint64_t N = 1;
  if (args != NULL) {
    N = atoi(args);
  }
  runN(N);
  return 0;
}
static struct {
  const char *name;
  const char *description;
  int (*handler)(char *);
} cmd_table[] = {
    {"si", "Run N lines of code", simulate}
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
int main(int argc, char **argv, char **env) {
  //nvboard_bind_all_pins(top);
  //nvboard_init();
  initMemory(argc, argv); // 会自动加载程序
  contextp->traceEverOn(true);
  contextp->commandArgs(argc, argv);
  VerilatedVcdC *vcd = new VerilatedVcdC();
  top->trace(vcd, 0);
  vcd->open("data.vcd");
  int time = 0;
  top->rst = 0;
  top->eval();
  top->rst = 1;
  top->eval();
  top->rst = 0;
  top->clk = 0;
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
        if (cmd_table[i].handler(args) < 0) {
          return 0;
        }
        break;
      }
    }

    if (i == NR_CMD) {
      printf("Unknown command '%s'\n", cmd);
    }
  }
  
  if (sebreak) {
    if (cpu_gpr [10] == 0) {
      printf("HIT GOOD TRAP.\n");
    } else {
      printf("HIT BAD TRAP. code is %lx\n", cpu_gpr [10]);
      return cpu_gpr [10];
    }
  }
  top->final();
  vcd->close();
  return 0;
}
