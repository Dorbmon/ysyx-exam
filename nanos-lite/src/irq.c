#include <common.h>
void do_syscall(Context *c, Context** ret);
static Context* do_event(Event e, Context* c) {
  Context* ret = c;
  switch (e.event) {
    case EVENT_SYSCALL: do_syscall(c, &ret); break;
    case EVENT_YIELD: printf("catched yield...\n"); break;
    default: panic("Unhandled event ID = %d", e.event);
  }
  return ret;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
