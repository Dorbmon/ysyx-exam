#ifndef ITRACE_H
#define ITRACE_H
#include "debug.h"
extern "C" {
    void init_disasm(const char *triple);
    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
}
void loadINST(uint32_t rinst, uint32_t pc);
#define BITMASK(bits) ((1ull << (bits)) - 1)
#define BITS(x, hi, lo) (((x) >> (lo)) & BITMASK((hi) - (lo) + 1)) // similar to x[hi:lo] in verilog
#define SEXT(x, len) ({ struct { int64_t n : len; } __x = { .n = x }; (uint64_t)__x.n; })
#define OUPUT_INST
#define ENABLE_FTRACE
#endif