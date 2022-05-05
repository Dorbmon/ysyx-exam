#ifndef DIFF_H
#define DIFF_H
#include "memory.h"
#include "isa.h"
extern char* diff_so;
void initDiffset();
void difftest_step(paddr_t pc, paddr_t npc);
struct diff_context_t {
  word_t* gpr;
  word_t pc;
} ;
extern diff_context_t cpu;
#endif
