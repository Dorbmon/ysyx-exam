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
  pcb->cp = kcontext(kstack, entry, arg);
}
void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%p' for the %dth time!", (uintptr_t)arg, j);
    j ++;
    yield();
  }
}
void naive_uload(PCB *pcb, const char *filename);
void init_proc() {
  context_kload(&pcb[0], hello_fun, NULL);
  switch_boot_pcb();
  
  Log("Initializing processes...");

  // load program here
  naive_uload(NULL, "/bin/nterm");
}
// 返回新的上下文
Context* schedule(Context *prev) {
  // 先保存当前的上下文
  current->cp = prev;
  current = &pcb[0]; // 选择第一个
  return current->cp;
}
