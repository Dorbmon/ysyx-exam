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
void ebreak() {
  sebreak = true;
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
  while (!contextp->gotFinish() && !sebreak && time < 10) {
    //contextp->timeInc(1);
    //vcd->dump(time);
    time ++;
    if (time & 1) {
      printf("pc:%lx\n", top->pc);
    }
    top->clk = ~top->clk;
    top->inst = pmem_read(top->pc, 4);
    //std::cout << "Here" << std::endl;
    top->eval();

    //nvboard_update();
  }
  if (sebreak) {
    printf("EBreak.\n");
  }
  top->final();
  vcd->close();
  return 0;
}
