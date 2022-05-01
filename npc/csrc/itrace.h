#ifndef ITRACE_H
#define ITRACE_H
#include "debug.h"
extern "C" {
    void init_disasm(const char *triple);
    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
}
void loadINST(uint8_t inst, uint32_t pc);
#endif