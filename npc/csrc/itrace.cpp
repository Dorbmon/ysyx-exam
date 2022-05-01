#include "itrace.h"
#include "elf.h"
#include <cstring>
#include "isa.h"
static word_t immI(uint32_t i) { return SEXT(BITS(i, 31, 20), 12); }
static word_t immU(uint32_t i) { return SEXT(BITS(i, 31, 12) << 12, 32) ; }
static word_t immS(uint32_t i) { return SEXT((BITS(i, 31, 25) << 5) | BITS(i, 11, 7), 12); }
static word_t immJ(uint32_t i) {return  SEXT((BITS(i, 31, 31) << 20) | (BITS(i, 30, 21) << 1) | (BITS(i, 20, 20) << 11) | (BITS(i, 19, 12) << 12), 21); }
static word_t immB(uint32_t i) {return SEXT((BITS(i, 31, 31) << 12) | (BITS(i, 30, 25) << 5) | (BITS(i, 11, 8) << 1) | (BITS(i, 7, 7) << 11), 13);}
int depth = 0;
void loadINST(uint32_t rinst, uint32_t pc) {
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
  #ifdef ENABLE_FTRACE
    uint32_t opcode = BITS(rinst, 6, 0);
    printf("opcode:%x\n", opcode);
    if (opcode == 0b1101111) {  // jal
      uint32_t dnpc = pc + immJ(rinst);
      if (strcmp(getBelongFunction(dnpc), getBelongFunction(pc)) != 0) {
        printf("%x:%*scall [%s@%x]\n", pc, (depth++) * 2, "", getBelongFunction(dnpc), dnpc);
      }
    } else if (opcode == 0b1100111) {
      uint32_t src1 = BITS(rinst, 19, 15);
      uint32_t dnpc = cpu_gpr[src1] + immI(rinst);
      if (strcmp(getBelongFunction(dnpc), getBelongFunction(pc)) != 0) {
        printf("%x:%*sret [%s@%x]\n",pc,(--depth) * 2, "", getBelongFunction(dnpc), dnpc);
      }
    }

  #endif
}