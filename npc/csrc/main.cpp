#include <memory>
#include <nvboard.h>
#include <Vtop.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
double sc_time_stamp() { return 0; }
const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
Vtop* top = new Vtop{contextp.get(), "TOP"};
void nvboard_bind_all_pins(Vtop* top);
void single_cycle() {
  top->eval();
  top->eval();
}
void reset(int n) {
  //top->rst = 1;
  while (n -- > 0) single_cycle();
 // top->rst = 0;
}
int main(int argc, char **argv, char **env) {
  nvboard_bind_all_pins(top);
  nvboard_init();
  
  contextp->traceEverOn(true);
  contextp->commandArgs(argc, argv);
  VerilatedVcdC *vcd = new VerilatedVcdC();
  
  top->trace(vcd, 0);
  vcd->open("data.vcd");
  int time = 0;
  reset(10);
  while (!contextp->gotFinish()) {
    contextp->timeInc(1);
    vcd->dump(time);
    time ++;
    single_cycle();
    nvboard_update();
  }
  top->final();
  vcd->close();
  return 0;
}
