#include <common.h>
#include "syscall.h"
#include <fs.h>
extern Finfo file_table[];
void sys_write(Context *c) {
  if (c->GPR2 == 1 || c->GPR2 == 2) { //stdout || stderr
    for (int i = 0;i < c->GPR4;++ i) {
      putch(*((uint8_t*)(c->GPR3) + i));
    }
    //asm volatile ("addi a0, %0, 0;" : : "r"(c->GPR4) : );
    c->GPRx = c->GPR4;
  }
}
void sys_brk(Context *c) {
  c->GPRx = 0;
}
struct FDescription {
  int index;
  int offset;
} fss [1000];
static int fssIndex = 0;
void sys_open(Context *c) {
  c->GPRx = fs_open((char*)c->GPR2, 0, 0);
}
int fs_open(const char *pathname, int flags, int mode) {
  for (int i = 0;i < ARRLEN(file_table); ++ i) {
    if (strcmp(file_table[i].name, pathname) == 0) {
      ++ fssIndex;
      fss [fssIndex].index = i;
      fss [fssIndex].offset = 0;
      return fssIndex;
    }
  }
  assert(0);
  return -1;
}
size_t fs_read(int fd, void *buf, size_t len) {
  size_t ramdisk_read(void *buf, size_t offset, size_t len);
  if (fss[fd].index < 3) return 0;
  int i = fss[fd].index;
  int ret = ramdisk_read(buf, file_table[i].disk_offset + fss[fd].offset, len);
  fss[fd].offset += ret;
  return ret;
}
void sys_read(Context *c) {
  c->GPRx = fs_read(c->GPR2, (void*)c->GPR3, c->GPR4);
}
size_t fs_write(int fd, const void *buf, size_t len) {
  size_t ramdisk_write(const void *buf, size_t offset, size_t len);
  if (fss[fd].index < 3) return 0;
  int i = fss[fd].index;
  int ret = ramdisk_write(buf, file_table[i].disk_offset + fss[fd].offset, len);
  fss[fd].offset += ret;
  return ret;
}
size_t fs_lseek(int fd, size_t offset, int whence) {
  int i = fss[fd].index;
  switch (whence) {
  case SEEK_SET:
  {
    fss[fd].offset = offset;
    break;
  }
  case SEEK_END:
  {
    fss[fd].offset = file_table[i].size + offset;
    break;
  }
  case SEEK_CUR:
  {
    fss[fd].offset += offset;
    break;
  }
  default: assert(0);
  }
  return fss[fd].offset;
}
void sys_lseek(Context *c) {
  c->GPRx = fs_lseek(c->GPR2, c->GPR3, c->GPR4);
}
void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  switch (a[0]) {
    case SYS_yield: break;  //SYS_yield
    case SYS_exit: halt(c->GPR2); break;
    case SYS_write: sys_write(c); break;
    case SYS_brk: sys_brk(c); break;
    case SYS_open: sys_open(c); break;
    case SYS_read: sys_read(c); break;
    case SYS_lseek: sys_lseek(c); break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
