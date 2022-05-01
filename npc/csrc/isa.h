#ifndef ISA_H
#define ISA_H
#include "memory.h"
#include <Vysyx_22041207_top.h>
word_t isa_reg_str2val(const char *name, bool *success);
extern Vysyx_22041207_top* top;
void isa_reg_display();
#endif