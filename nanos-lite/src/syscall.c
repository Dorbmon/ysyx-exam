#include <common.h>
#include "syscall.h"
#include <fs.h>
#include <proc.h>
extern Finfo file_table[];
void sys_write(Context *c) {
  c->GPRx = fs_write(c->GPR2, (void*)c->GPR3, c->GPR4);
}
int mm_brk(Context *c, uintptr_t brk);
void sys_brk(Context *c) {
  uint64_t addr = c->GPR2;
  c->GPRx = mm_brk(c, addr);
}
void sys_open(Context *c) {
  c->GPRx = fs_open((char*)c->GPR2, 0, 0);
}
void toLower(char *tar,const char* src) {
  while (*src != '\0') {
    if (*src >= 'A' && *src <= 'Z') {
      *tar = *src - 'A' + 'a';
    } else {
      *tar = *src;
    }
    ++ tar;
    ++ src;
  }
  *tar = '\0';
}
int fs_open(const char *pathname, int flags, int mode) {
  char tmpFileName[50], tmp[50];
  toLower(tmpFileName, pathname);
  for (int i = 0;i < ARRLEN(file_table); ++ i) {
    toLower(tmp, file_table[i].name);
    if (strcmp(tmp, tmpFileName) == 0) {
      return i;
    }
  }
  printf("file:%s\n", pathname);
  assert(0);
  return -1;
}
size_t fs_read(int fd, void *buf, size_t len) {
  size_t ramdisk_read(void *buf, size_t offset, size_t len);
  if (fd < SPECIAL_NUM) {
    int ret = file_table[fd].read(buf, file_table[fd].open_offset, len);
    file_table[fd].open_offset += ret;
    return ret;
  }
  if (file_table[fd].open_offset + len > file_table[fd].size) {
    len = file_table[fd].size - file_table[fd].open_offset;
  }
  int ret = ramdisk_read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
  file_table[fd].open_offset += ret;
  return ret;
}
void sys_read(Context *c) {
  c->GPRx = fs_read(c->GPR2, (void*)c->GPR3, c->GPR4);
}
size_t fs_write(int fd, const void *buf, size_t len) {
  size_t ramdisk_write(const void *buf, size_t offset, size_t len);
  if (fd < SPECIAL_NUM) {
    int ret = file_table[fd].write(buf, file_table[fd].open_offset, len);
    file_table[fd].open_offset += ret;
    return ret;
  }
  if (file_table[fd].open_offset + len > file_table[fd].size) {
    len = file_table[fd].size - file_table[fd].open_offset;
  }
  int ret = ramdisk_write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
  file_table[fd].open_offset += ret;
  return ret;
}
size_t fs_lseek(int fd, size_t offset, int whence) {
  switch (whence) {
  case SEEK_SET:
  {
    file_table[fd].open_offset = offset;
    break;
  }
  case SEEK_END:
  {
    file_table[fd].open_offset = file_table[fd].size + offset;
    break;
  }
  case SEEK_CUR:
  {
    file_table[fd].open_offset += offset;
    break;
  }
  default: assert(0);
  }
  return file_table[fd].open_offset;
}
int fs_close(int fd) {
  file_table[fd].open_offset = 0;
  return 0;
}
void sys_lseek(Context *c) {
  c->GPRx = fs_lseek(c->GPR2, c->GPR3, c->GPR4);
}
void naive_uload(PCB *pcb, const char *filename);
int execve(const char *fname, char * const argv[], char *const envp[]) {
  naive_uload(NULL, fname);
  return 0;
}
void sys_execve(Context *c) {
  c->GPRx = execve((const char *)c->GPR2, (char * const*)c->GPR3, (char *const*)c->GPR4);
}
void sys_close(Context *c) {
  c->GPRx = fs_close(c->GPR2);
}
struct timeval 
{
    long int  tv_sec;     /* 获取的秒数 */
    long int tv_usec;    /* 获取的微秒数 */
};

struct timezone {
  int tz_minuteswest;     /* minutes west of Greenwich */
  int tz_dsttime;         /* type of DST correction */
};
void sys_gettimeofday(Context *c) {
  //volatile uint64_t time = *(uint64_t*)(0xa0000048);
  uint64_t time = io_read(AM_TIMER_UPTIME).us;
  //printf("rtime:%ld\n", time);
  struct timeval*tv = (struct timeval*)(c->GPR2);
  tv->tv_sec = time / 1000000;
  tv->tv_usec = time;
  c->GPRx = 0;
}
void sys_yield(Context* c, Context** ret) {
  *ret = schedule(c);
}
void do_syscall(Context *c, Context** ret) {
  switch (c->GPR1) {
    case SYS_yield: sys_yield(c, ret); break;  //SYS_yield
    //case SYS_exit: halt(c->GPR2); break;
    case SYS_exit: naive_uload(NULL, "/bin/menu"); break;
    case SYS_write: sys_write(c); break;
    case SYS_brk: sys_brk(c); break;
    case SYS_open: sys_open(c); break;
    case SYS_close: sys_close(c); break;
    case SYS_read: sys_read(c); break;
    case SYS_lseek: sys_lseek(c); break;
    case SYS_execve: sys_execve(c); break;
    case SYS_gettimeofday: sys_gettimeofday(c); break;
    default: panic("Unhandled syscall ID = %d", c->GPR1);
  }
}
