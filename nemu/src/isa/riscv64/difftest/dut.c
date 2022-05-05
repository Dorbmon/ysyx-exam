#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  for (int i = 0;i < 32;++ i) {
    //printf("%lx %lx\n", ref_r->gpr [i], cpu.gpr [i]);
    if (ref_r->gpr [i] != cpu.gpr [i]) {
      printf("reg:x%d: %lx %lx\n", i, ref_r->gpr [i], cpu.gpr [i]);
      return false;
    }
  }
  printf("%lx %lx %lx\n", pc, ref_r->pc, cpu.pc);
  return ref_r->pc == cpu.pc;
}

void isa_difftest_attach() {
}
