#include "isa.h"
#include <string.h>
#include "macro.h"
#include "diff.h"

void isa_reg_display() {
  for (int i = 0;i < 32;++ i) {
    printf("%s %lx \n",regs[i], cpu.gpr[i]);
  }
}

word_t isa_reg_str2val(const char *s, bool *success) {
  for (int i = 0;i < ARRLEN(regs); ++ i) {
    if (strcmp(regs[i], s) == 0) {
      *success = true;
      return cpu.gpr[i];
    }
  }
  *success = false;
  return 0;
}
