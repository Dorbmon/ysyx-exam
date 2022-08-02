#include <stdint.h>
#include <stdio.h>
#ifdef __ISA_NATIVE__
#error can not support ISA=native
#endif

#define SYS_yield 1
#define SYS_write 4
extern int _syscall_(int, uintptr_t, uintptr_t, uintptr_t);

int main() {
  printf("start to run dummy....\n");
  //putchar('R');
  //while (1);
  //char t[] = "hello world";
  //_syscall_(SYS_write, 1, (uintptr_t)t, sizeof(t));
  while (1);
  //return 0;
  //return _syscall_(SYS_exit, 0, 0, 0);
}
