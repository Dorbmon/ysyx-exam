#ifndef MEMORYH
#define MEMORYH
#include <memory>
#include <assert.h>
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR 0x80000000
typedef uint64_t word_t;
typedef uint64_t paddr_t;
typedef uint64_t word_t;
void initMemory(const char* img_file);
word_t pmem_read(paddr_t addr, int len);
uint8_t* guest_to_host(paddr_t paddr);
extern long img_size;
void pBin(long int x);
#endif