#include <am.h>
#include <nemu.h>
#include <klib.h>

// 内核空间
static AddrSpace kas = {};
static void* (*pgalloc_usr)(int) = NULL;
static void (*pgfree_usr)(void*) = NULL;
static int vme_enable = 0;
// typedef struct {
//   int pgsize;
//   Area area;
//   void *ptr;
// } AddrSpace;
static Area segments[] = {      // Kernel memory mappings
  NEMU_PADDR_SPACE
};

#define USER_SPACE RANGE(0x40000000, 0x80000000)  // 1MB
static inline void set_satp(void *pdir) {
  uint64_t mode = 1ull << (__riscv_xlen - 1);
  asm volatile("csrw satp, %0" : : "r"(mode | ((uint64_t)pdir >> 12)));
}
// 0x180 satp
static inline uintptr_t get_satp() {
  uintptr_t satp;
  asm volatile("csrr %0, satp" : "=r"(satp));
  return satp << 12;
}

bool vme_init(void* (*pgalloc_f)(int), void (*pgfree_f)(void*)) {
  pgalloc_usr = pgalloc_f;
  pgfree_usr = pgfree_f;

  kas.ptr = pgalloc_f(PGSIZE);
  int i;
  for (i = 0; i < LENGTH(segments); i ++) { // 访问页表索引
    void *va = segments[i].start; // 处理这个页表中的所有页面
    for (; va < segments[i].end; va += PGSIZE) {
      map(&kas, va, va, 0);
    }
  }
  set_satp(kas.ptr);
  vme_enable = 1;

  return true;
}

void protect(AddrSpace *as) {
  PTE *updir = (PTE*)(pgalloc_usr(PGSIZE));
  as->ptr = updir;
  as->area = USER_SPACE;
  as->pgsize = PGSIZE;
  // map kernel space
  memcpy(updir, kas.ptr, PGSIZE);
}

void unprotect(AddrSpace *as) {
}

void __am_get_cur_as(Context *c) {
  c->pdir = (vme_enable ? (void *)get_satp() : NULL);
}

void __am_switch(Context *c) {
  if (vme_enable && c->pdir != NULL) {
    //printf("set...\n");
    set_satp(c->pdir);
  }
}
#define ext2(x, s, t) ((x >> s) & ((1ull << (t - s + 1)) - 1))
void map(AddrSpace *as, void *va, void *pa, int prot) {
  if (vme_enable) {
  // 将as中的va所在的虚拟页映射到pa所在的物理页
  //pa = ((size_t)va >> 12) << 12;
  //pa = ((size_t)pa >> 12) << 12;
  // 提取第一级
  size_t l1 = ext2((size_t)va, 30, 38), l2 = ext2((size_t)va, 21, 29), l3 = ext2((size_t)va, 12, 20);
  uint64_t* t = (uint64_t*) ((size_t)as->ptr + l1 * 8);  // 第一级对应的表项
  //printf("l1:%x\n", l1);
  if (*t == 0) {  // 这一项还没有初始化过
    // 为他创建一个表
    uint64_t pptr = (uint64_t)pgalloc_usr(PGSIZE);
    *t = (pptr >> 12) << 10;// 低12位舍弃
  }
  uint64_t addr = ext2(*t, 10, 47);
  addr <<= 12;
  addr += l2 * 8; // 第二个表
  t = (uint64_t*)addr;
  if (*t == 0) {  // 这一项还没有初始化过
    // 为他创建一个表
    uint64_t pptr = (uint64_t)pgalloc_usr(PGSIZE);
    *t = (pptr >> 12) << 10;// 低12位舍弃
  }
  addr = ext2(*t, 10, 47);
  addr <<= 12;
  addr += l3 * 8;
  //printf("addr:%x\n", addr);
  t = (uint64_t*)addr;  // 最终表 代表着最后一次映射
  if (*t == 0) {  // 这一项还没有初始化过
    uint64_t pptr = (uint64_t)pa;
    *t = (pptr >> 12) << 10;// 低12位舍弃
  }
  }
}

Context *ucontext(AddrSpace *as, Area kstack, void *entry) {
  Context* context = (Context*)((intptr_t)kstack.end - sizeof(Context));
  // 设置entry为返回地址
  context->mepc = (intptr_t)entry;
  //Log("mepc: %x", context->mepc);
  context->mstatus = 0xa00001800;
  context->pdir = as->ptr;
  //context->gpr[10] = (intptr_t)arg; //a0
  return context;
}
