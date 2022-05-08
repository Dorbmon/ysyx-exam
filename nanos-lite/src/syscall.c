#include <common.h>
#include "syscall.h"
void sys_write(Context *c) {
  if (c->GPR2 == 1 || c->GPR2 == 2) { //stdout || stderr
    //printf("print:%d\n", c->GPR4);
    for (int i = 0;i < c->GPR4;++ i) {
      putch(*((uint8_t*)(c->GPR3) + i));
    }
    asm volatile ("addi a0, %0, 0;" : : "r"(c->GPR4) : );
  }
}
void sys_brk(Context *c) {
  asm volatile ("addi a0, x0, 0" : :  );
}
void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;

  switch (a[0]) {
    case SYS_yield: break;  //SYS_yield
    case SYS_exit: halt(c->GPR2); break;
    case SYS_write: sys_write(c); break;
    case SYS_brk: sys_brk(c); break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
