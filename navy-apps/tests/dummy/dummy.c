#include <stdint.h>
#include <stdio.h>
#ifdef __ISA_NATIVE__
#error can not support ISA=native
#endif

#define SYS_yield 1
extern int _syscall_(int, uintptr_t, uintptr_t, uintptr_t);

int main() {
  //printf("start to run dummy....\n");
  putchar('R');
  while (1);
  //return _syscall_(SYS_exit, 0, 0, 0);
}
