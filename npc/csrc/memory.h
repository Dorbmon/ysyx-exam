#ifndef MEMORYH
#define MEMORYH
#include <memory>
#include <assert.h>
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR 0x80000000
typedef uint64_t word_t;
typedef uint64_t paddr_t;
typedef uint64_t word_t;
void initMemory(int argc,char** argv);
word_t pmem_read(paddr_t addr, int len);
#endif