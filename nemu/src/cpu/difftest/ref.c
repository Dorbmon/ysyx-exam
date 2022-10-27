#include <isa.h>
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>
// DIFFTEST_TO_REF 1
void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  if (direction) {
    for (size_t i = 0;i < n;++ i) {
      //*(uint8_t*)(buf+i) = paddr_read(addr, 1);
      paddr_write(addr + i, 1,*((uint8_t*)buf + i));
    }
  } else {
    assert(0);
  }
}
struct diff_context_t {
  word_t* gpr;
  word_t pc;
};
void difftest_regcpy(void *dut, bool direction) {
  if (direction) {
    struct diff_context_t* ctx = (struct diff_context_t*)dut;
    for (int i = 0; i < 32; i++) {
      cpu.gpr[i] = ctx->gpr[i];
    }
    cpu.pc = ctx->pc;
  } else {
    struct diff_context_t* ctx = (struct diff_context_t*)dut;
    for (int i = 0; i < 32; i++) {
      ctx->gpr[i] = cpu.gpr[i];
    }
    ctx->pc = cpu.pc;
  }
}

void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

void difftest_raise_intr(word_t NO) {
  assert(0);
}

void difftest_init(int port) {
  /* Perform ISA dependent initialization. */
  init_isa();
}
