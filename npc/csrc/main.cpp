#include <memory>

#include "Vtop.h"
#include <verilated.h>
#include <verilated_vcd_c.h>

double sc_time_stamp() { return 0; }

int main(int argc, char **argv, char **env) {
  if (false && argc && argv && env) {
  }
  const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
  contextp->traceEverOn(true);
  contextp->commandArgs(argc, argv);
  VerilatedVcdC *vcd = new VerilatedVcdC();
  const std::unique_ptr<Vtop> top{new Vtop{contextp.get(), "TOP"}};
  top->trace(vcd, 0);
  vcd->open("data.vcd");
  int time = 0;
  while (time < 20 && !contextp->gotFinish()) {
    contextp->timeInc(1);
    int a = rand() & 1;
    int b = rand() & 1;
    top->a = a;top->b = b;
    top->eval();
    vcd->dump(time);
    printf("%d %d %d\n",a,b,top->f);
    //std::cout << a << " " << b << " " << top->f << std::endl;
    time ++;
  }
  top->final();
  vcd->close();
  return 0;
}
