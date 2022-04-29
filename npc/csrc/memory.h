#ifndef MEMORYH
#define MEMORYH
#include <memory>
#include <assert.h>
typedef uint64_t word_t;
typedef uint64_t paddr_t;
typedef uint64_t word_t;
void initMemory(int argc,char** argv);
word_t pmem_read(paddr_t addr, int len);
#endif