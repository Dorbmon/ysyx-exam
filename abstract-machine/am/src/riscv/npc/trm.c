#include <am.h>
#include <klib-macros.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
  //outb(0xA00003F8, ch);
  *((uint8_t*)0xA00003F8) = ch;
}

void halt(int code) {
  asm volatile("addi x10, %0, 0;ebreak":: "r"(code):);
  while (1);
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
