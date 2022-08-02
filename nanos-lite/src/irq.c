#include <common.h>
void do_syscall(Context *c, Context** ret);
void sys_yield(Context* c, Context** ret);
static Context* do_event(Event e, Context* c) {
  Context* ret = c;
  switch (e.event) {
    case EVENT_SYSCALL: do_syscall(c, &ret); break;
    case EVENT_YIELD: sys_yield(c, &ret); break;
    default: panic("Unhandled event ID = %d", e.event);
  }
  ret->mepc += 4;
  return ret;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
