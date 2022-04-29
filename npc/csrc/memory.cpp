#ifndef RMemory
#include "memory.h"
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR 0x80000000
#define kDisplayWidth 32
static void pBin(long int x)
{
 char s[kDisplayWidth+1];
 int  i=kDisplayWidth;
 s[i--]=0x00;
 do
 {
  s[i--]=(x & 1) ? '1':'0';
  x>>=1;
 } while( x > 0);
 while(i>=0) s[i--]='0';
 printf("%s\n",s);
 return ;
}

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

word_t pmem_read(paddr_t addr, int len) {
  word_t ret = host_read(guest_to_host(addr), len);
  return ret;
}
static char *img_file = NULL;
void initMemory(int argc,char** argv) {
  assert(argc == 2);
  //char *img_file = argv[1];
  char* img_file = "/home/dorbmon/ysyx/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-riscv64-nemu.bin";
  printf("load img file:%s\n", img_file);
  FILE *fp = fopen(img_file, "rb");
  assert(fp != NULL);
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);
  fclose(fp);
  for (paddr_t addr = 0; addr <= 1000; addr += 4) {
    //pBin(pmem_read(addr, 4));
    pBin(*(uint32_t*)(pmem + addr));
  }
}
#endif