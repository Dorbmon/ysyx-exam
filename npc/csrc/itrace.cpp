#include "itrace.h"

void loadINST(uint8_t rinst, uint32_t pc) {
  char logbuf [128];
  char *p = logbuf;
  char* begin = logbuf;
  p += snprintf(p, sizeof(logbuf), FMT_WORD ":", pc);
  uint8_t *inst = (uint8_t *)&rinst;
  for (int i = 4 - 1; i >= 0; i --) {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int space_len = 1;
  memset(p, ' ', space_len);
  p += space_len;
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, logbuf + sizeof(logbuf) - p,
      pc, (uint8_t *)&rinst, 4);
  printf("%s \n", logbuf);
}