#include <cstdio>
#ifndef RMemory
#include "memory.h"
#include "debug.h"
#include <iostream>
#include <sys/time.h>
#define kDisplayWidth 32
void pBin(long int x)
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

static uint8_t pmem[0x2000000] __attribute((aligned(4096))) = {};
static inline word_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    case 8: return *(uint64_t *)addr;
    default: assert(0);
  }
}
static inline void host_write(void *addr, int len, word_t data) {
  switch (len) {
    case 1: *(uint8_t  *)addr = data; return;
    case 2: *(uint16_t *)addr = data; return;
    case 4: *(uint32_t *)addr = data; return;
    case 8: *(uint64_t *)addr = data; return;
  }
}
static void rpmem_write(paddr_t addr, int len, word_t data) {
  host_write(guest_to_host(addr), len, data);
}
uint8_t* guest_to_host(paddr_t paddr) { return pmem + paddr - CONFIG_MBASE; }
paddr_t host_to_guest(uint8_t *haddr) { return haddr - pmem + CONFIG_MBASE; }

word_t pmem_read(paddr_t addr, int len) {
  word_t ret = host_read(guest_to_host(addr), len);
  return ret;
}
long img_size = 0;
void initMemory(const char *img_file) {
  //img_file = "/home/dorbmon/ysyx/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-riscv64-nemu.bin";
  printf("load img file:%s\n", img_file);
  FILE *fp = fopen(img_file, "rb");
  assert(fp != NULL);
  fseek(fp, 0, SEEK_END);
  img_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), img_size, 1, fp);
  assert(ret == 1);
  fclose(fp);
}
extern "C" void pmem_read(long long raddr, long long *rdata) {
  // 总是读取地址为`raddr & ~0x7ull`的8字节返回给`rdata`
  //if ((raddr & ~0x7ull) < CONFIG_MBASE) return ;
  if (raddr == 0xa0000048 || raddr == 0xa0000050) {  // rtc
    timeval t;
    gettimeofday( &t, NULL );
    //uint32_t* tmp = (uint32_t*)rdata;
    if (raddr == 0xa0000048) {
      //*rdata = t.tv_usec << 32;
      *rdata = t.tv_usec;
    } else {
      //*rdata = t.tv_usec;
      *rdata = t.tv_usec>>32;
    }
    return ;
  }
  raddr &= ~0x7ull;
  printf("read address:%x\n", raddr);
  
  *rdata = pmem_read(raddr, 8); //111
  //printf("read:%llx, but:%llx", raddr, raddr & ~0x7ull);
}
static void serial_io_handler(uint32_t offset, int len, bool is_write, char rdata) {
  assert(len == 1);
  switch (offset) {
    /* We bind the serial port with the host stderr in NEMU. */
    case 0:
      if (is_write) putchar(rdata);
      else panic("do not support read");
      break;
    default: panic("do not support offset = %d", offset);
  }
}
extern "C" void pmem_write(long long waddr, long long wdata, char wmask) {
  if (wmask == 0) return ;
  //0xa00003f8
  //printf("write:%llx but:%llx\n", waddr, waddr & ~0x7ull);
  // 总是往地址为`waddr & ~0x7ull`的8字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
  waddr &= ~0x7ull;
  //printf("catch memory write:%lx \n", waddr);
  if (waddr == 0xa00003f8) {
    serial_io_handler(0, wmask == 1,true, wdata);
    return ;
  }
  word_t v = pmem_read(waddr, 8);
  word_t nv = 0;
  for (int i = 0;i < 8;++ i) {
    if (wmask & (1 << i)) { // 第i个字节需要写入
      nv |= ((wdata >> (i * 8)) & ((1 << 8) - 1)) << (i * 8);
    } else {
      nv |= ((v >> (i * 8)) & ((1 << 8) - 1)) << (i * 8);
    }
  }
  rpmem_write(waddr, 8, nv);
}
#endif