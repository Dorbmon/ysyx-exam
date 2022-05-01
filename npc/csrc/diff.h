#ifndef DIFF_H
#define DIFF_H
#include "memory.h"
#include "isa.h"
extern char* diff_so;
void initDiffset();
void difftest_step(paddr_t pc, paddr_t npc);
static struct diff_context_t {
  word_t* gpr;
  word_t pc;
} cpu;
#endif
