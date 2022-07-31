#include <proc.h>

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;

void switch_boot_pcb() {
  current = &pcb_boot;
}
Context *kcontext(Area kstack, void (*entry)(void *), void *arg);
void context_kload(PCB *pcb, void (*entry)(void *), void *arg) {
  Area kstack;
  kstack.start = (void*)((intptr_t)pcb);
  kstack.end   = (void*)((intptr_t)pcb + sizeof(PCB));
  //printf("%ld %ld\n", kstack.start, kstack.end);
  pcb->cp = kcontext(kstack, entry, arg);
  assert(pcb->cp != NULL);
}
void hello_fun(void *arg) {
  Log("enter function...");
  size_t j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%s' for the %ldth time!\n", arg, j ++);
    yield();
  }
}
void naive_uload(PCB *pcb, const char *filename);
void init_proc() {
  context_kload(&pcb[0], hello_fun, "f1");
  context_kload(&pcb[1], hello_fun, "f2");

  switch_boot_pcb();
  Log("Initializing processes...");

  // load program here
  //naive_uload(NULL, "/bin/dummy");
}
// 返回新的上下文
Context* schedule(Context *prev) {
  Log("mepc:%x", prev->mepc);
  // 先保存当前的上下文
  current->cp = prev;
  current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
  //current = &pcb[0]; // 选择第一个
  //Log ("Get mstatus:%x", prev->mstatus);
  assert(current->cp != NULL);
  return current->cp;
}
