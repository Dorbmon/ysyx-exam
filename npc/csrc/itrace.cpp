#include "itrace.h"

void loadINST(uint8_t inst, uint32_t pc) {
  char logbuf [128];
  char *p = logbuf;
  char *begin = logbuf;
  p += snprintf(p, sizeof(logbuf), FMT_WORD ":", pc);
  disassemble(p, logbuf + sizeof(logbuf) - p,
              pc,
              (uint8_t *)&inst, 4);
}