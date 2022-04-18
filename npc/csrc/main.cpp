#include <memory>
#include <nvboard.h>
#include <Vtop.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>
double sc_time_stamp() { return 0; }
const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
Vtop* top = new Vtop{contextp.get(), "TOP"};
void nvboard_bind_all_pins(Vtop* top);
int main(int argc, char **argv, char **env) {
  nvboard_bind_all_pins(top);
  nvboard_init();
  
  contextp->traceEverOn(true);
  contextp->commandArgs(argc, argv);
  VerilatedVcdC *vcd = new VerilatedVcdC();
  
  top->trace(vcd, 0);
  vcd->open("data.vcd");
  int time = 0;
  while (!contextp->gotFinish()) {
    //contextp->timeInc(1);
    //vcd->dump(time);
    //time ++;
    top->clk = ~top->clk;
    std::cout << "Here" << std::endl;
    top->eval();
    nvboard_update();
  }
  top->final();
  vcd->close();
  return 0;
}
