#include <memory.h>

static void *pf = NULL;

void* new_page(size_t nr_page) {
  void* ret = pf;
  pf = (void*)((size_t)pf + nr_page * 4 * 1024);
  return ret;
}

#ifdef HAS_VME
static void* pg_alloc(int n) {
  // n 个字节
  // 一页4kb = 4 * 1024字节
  size_t pageNum = n / 4 / 1024;
  if (pageNum * 4 * 1024 != n) ++ pageNum;
  void* res = new_page(pageNum);
  memset(res, 0, pageNum * PGSIZE);
  return res;
}
#endif

void free_page(void *p) {
  panic("not implement yet");
}

/* The brk() system call handler. */
int mm_brk(uintptr_t brk) {
  return 0;
}

void init_mm() {
  pf = (void *)ROUNDUP(heap.start, PGSIZE);
  Log("free physical pages starting from %p", pf);

#ifdef HAS_VME
  Log("start to init vme...");
  vme_init(pg_alloc, free_page);
#endif
}
