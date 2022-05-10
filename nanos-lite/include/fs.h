#ifndef __FS_H__
#define __FS_H__
#include <common.h>
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);
enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_EVENT, FD_DISPLAYINFO, FD_FB };
size_t invalid_read(void *buf, size_t offset, size_t len);
size_t invalid_write(const void *buf, size_t offset, size_t len);
size_t serial_write(const void *buf, size_t offset, size_t len);
typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;
size_t events_read(void *buf, size_t offset, size_t len);
size_t dispinfo_read(void *buf, size_t offset, size_t len);
#define SPECIAL_NUM 5
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, serial_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, serial_write},
  [FD_EVENT]  = {"/dev/events", 0, 0, events_read, invalid_write },
  [FD_DISPLAYINFO] = {"/proc/dispinfo", 0, 0, dispinfo_read, invalid_write },
#include "../src/files.h"
};
#ifndef SEEK_SET
enum {SEEK_SET, SEEK_CUR, SEEK_END};
#endif
int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);
#endif
