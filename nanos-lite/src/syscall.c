#include <common.h>
#include "syscall.h"

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;

  switch (a[0]) {
    case SYS_yield: break;  //SYS_yield
    case SYS_exit: halt(c->GPR2); break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
