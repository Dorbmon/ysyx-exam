#ifndef RMemory
#include <memory>
#include <assert.h>
#define CONFIG_MBASE 0x80000000
typedef uint64_t word_t;
typedef uint64_t paddr_t;
static uint32_t pmem[0x2000000] __attribute((aligned(4096))) = {};
static inline word_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    case 8: return *(uint64_t *)addr;
    default: assert(0);
  }
}
static uint32_t* guest_to_host(paddr_t paddr) { return pmem + paddr - CONFIG_MBASE; }
static paddr_t host_to_guest(uint32_t *haddr) { return haddr - pmem + CONFIG_MBASE; }

static word_t pmem_read(paddr_t addr, int len) {
  word_t ret = host_read(guest_to_host(addr), len);
  return ret;
}
static char *img_file = NULL;
void initMemory() {
  // 11111111110000010000000100010011
  //       imm111111111100
  //                    rs00010
  //                            rd00001s
  pmem[0] = 0b11111111110000000000000010010011;
  pmem[1] = 0b11111111110000010000000010010011;
  pmem[2] = 0b00000000000000000000000001110011;
}
#endif