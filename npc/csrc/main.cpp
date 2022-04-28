#include <memory>
#include <nvboard.h>
#include <Vysyx_22041207_top.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>
#include "memory.h"
#include "svdpi.h"
#include "Vysyx_22041207_top__Dpi.h"
double sc_time_stamp() { return 0; }
const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
Vysyx_22041207_top* top = new Vysyx_22041207_top{contextp.get(), "TOP"};
void nvboard_bind_all_pins(Vysyx_22041207_top* top);
bool sebreak = false;
void ebreak(int is) {
  sebreak = is;
}

int main(int argc, char **argv, char **env) {
  // 读入程序
  assert(argc == 2);
  char *img_file = argv[1];
  FILE *fp = fopen(img_file, "rb");
  assert(fp != NULL);
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);
  fclose(fp);

  //nvboard_bind_all_pins(top);
  //nvboard_init();
  initMemory();
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
  while (!contextp->gotFinish() && !sebreak) {
    //contextp->timeInc(1);
    //vcd->dump(time);
    //time ++;
    printf("pc:%u\n", top->pc);
    top->clk = ~top->clk;
    top->inst = pmem_read(top->pc, 4);
    //std::cout << "Here" << std::endl;
    top->eval();

    //nvboard_update();
  }
  top->final();
  vcd->close();
  return 0;
}
