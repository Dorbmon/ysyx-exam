#include <am.h>
#include <klib-macros.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef mainargs
#define mainargs ""
#endif
static const char tmainargs[] = mainargs;

void putch(char ch) {
}

void halt(int code) {
  asm volatile("addi x10, %0, 0;ebreak":: "r"(code):);
  while (1);
}

void _trm_init() {
  int ret = main(tmainargs);
  halt(ret);
}
