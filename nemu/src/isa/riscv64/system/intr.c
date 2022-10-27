#include <isa.h>

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  //printf("intr::::NO:%ld\n", NO);
  cpu.csrM [0x341] = epc;
  cpu.csrM [0x342] = NO;
  return cpu.csrM [0x305];
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
