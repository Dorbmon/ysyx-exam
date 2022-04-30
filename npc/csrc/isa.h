#ifndef ISA_H
#define ISA_H
#include "memory.h"
word_t isa_reg_str2val(const char *name, bool *success);
extern uint64_t* cpu_gpr;
#endif