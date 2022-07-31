#include <isa.h>
bool mpie;
word_t csrM[7424];
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  printf("intr::::NO:%ld\n", NO);
  csrM [0x341] = epc; //mepc
  //csrM [0x342] = NO;  //mcause
  csrM [0x342] = 0xb;
  uint64_t mstatus = csrM[0x300];
  mpie = mstatus & (1ull << 3);
  csrM[0x300] = mstatus & (~(1ull << 3));
  return csrM [0x305];
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
