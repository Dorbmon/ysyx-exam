#include <isa.h>
#define IRQ_TIMER 0x8000000000000007  // for riscv64
bool mpie;
word_t csrM[7424];
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  //printf("intr::::NO:%ld\n", NO);
  uint64_t mstatus = csrM[0x300];
  if (NO == IRQ_TIMER && (mstatus & (1ull << 3)) == 0ull) {
    return epc;
  } else if (NO == IRQ_TIMER) {
    printf("shit comming.....\n");
  }
    csrM [0x341] = epc; //mepc
    //csrM [0x342] = NO;  //mcause
    csrM [0x342] = NO; // 11 ecall
    
    mpie = mstatus & (1ull << 3);
    csrM[0x300] = mstatus & (~(1ull << 3)); // 关闭中断
    return csrM [0x305];
}

word_t isa_query_intr() {
  if (cpu.INTR) {
    cpu.INTR = false;
    return IRQ_TIMER;
  }
  return INTR_EMPTY;
}
