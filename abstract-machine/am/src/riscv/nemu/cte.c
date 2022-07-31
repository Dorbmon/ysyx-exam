#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    if (c->mcause == 0xb) {
    switch (c->GPR1) {
      case -1: ev.event = EVENT_YIELD;break;
      case 11: ev.event = EVENT_SYSCALL;break;
      case 0:ev.event = EVENT_SYSCALL;break;
      case 4:ev.event = EVENT_SYSCALL;break;
      case 9:ev.event = EVENT_SYSCALL;break;
      case 2:ev.event = EVENT_SYSCALL;break;
      case 3:ev.event = EVENT_SYSCALL;break;
      case 8:ev.event = EVENT_SYSCALL;break;
      case 19:ev.event = EVENT_SYSCALL;break;
      case 7:ev.event = EVENT_SYSCALL;break;
      case 13:ev.event = EVENT_SYSCALL;break;
      default: ev.event = EVENT_ERROR; break;
    }
    }
    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  // kstack.end就是顶端
  Context* context = (Context*)((intptr_t)kstack.end - sizeof(Context));
  // 设置entry为返回地址
  context->mepc = (intptr_t)entry;
  //Log("mepc: %x", context->mepc);
  context->mstatus = 0xa00001800;
  context->gpr[10] = (intptr_t)arg; //a0
  return context;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
