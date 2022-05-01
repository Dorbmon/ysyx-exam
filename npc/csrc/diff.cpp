#include "diff.h"

#include <dlfcn.h>
#include "common.h"
char *diff_so = NULL;
void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n,
                            bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
struct diff_context_t {
  word_t gpr[32];
  word_t pc;
} cpu;
static bool is_skip_ref = false;
static int skip_dut_nr_inst = 0;
void sync_cpu() {
  for (int i = 0; i < 32; ++i) {
    cpu.gpr[i] = cpu_gpr[i];
  }
  cpu.pc = top->pc;
}
void initDiffset() {
  assert(diff_so != NULL);
  void *handle;
  handle = dlopen(diff_so, RTLD_LAZY);
  assert(handle);
  printf("loaded so.\n");
  ref_difftest_memcpy =
      (void (*)(paddr_t, void *, size_t, bool))dlsym(handle, "difftest_memcpy");
  assert(ref_difftest_memcpy);

  ref_difftest_regcpy =
      (void (*)(void *, bool))dlsym(handle, "difftest_regcpy");
  assert(ref_difftest_regcpy);

  ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
  assert(ref_difftest_exec);

  void (*ref_difftest_init)(int) =
      (void (*)(int))dlsym(handle, "difftest_init");
  assert(ref_difftest_init);
  printf("loaded so.\n");
  ref_difftest_init(0); // 端口不影响 NEMU
  printf("loaded s23132132o.\n");
  ref_difftest_memcpy(RESET_VECTOR, guest_to_host(RESET_VECTOR), img_size, 1);
  sync_cpu();
  ref_difftest_regcpy(&cpu, 1);
}
bool isa_difftest_checkregs(diff_context_t *ref_r) {
  for (int i = 0;i < 32;++ i) {
    if (ref_r->gpr [i] != cpu.gpr [i]) return false;
  }
  return ref_r->pc == cpu.pc;
}
static void checkregs(diff_context_t *ref) {
  if (!isa_difftest_checkregs(ref)) {
    isa_reg_display();
    assert(0);
  }
}

void difftest_step(vaddr_t pc, vaddr_t npc) {
  diff_context_t ref_r;

  if (skip_dut_nr_inst > 0) {
    ref_difftest_regcpy(&ref_r, 1);
    if (ref_r.pc == npc) {
      skip_dut_nr_inst = 0;
      checkregs(&ref_r);
      return;
    }
    skip_dut_nr_inst --;
    if (skip_dut_nr_inst == 0)
      panic("can not catch up with ref.pc = " FMT_WORD " at pc = " FMT_WORD, ref_r.pc, pc);
    return;
  }

  if (is_skip_ref) {
    // to skip the checking of an instruction, just copy the reg state to reference design
    ref_difftest_regcpy(&cpu, 1);
    is_skip_ref = false;
    return;
  }

  ref_difftest_exec(1);
  ref_difftest_regcpy(&ref_r, 1);

  checkregs(&ref_r);
}