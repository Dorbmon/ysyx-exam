#include <fs.h>
int rfssIndex = 0;
size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */


void init_fs() {
  int width = io_read(AM_GPU_CONFIG).width, height = io_read(AM_GPU_CONFIG).height;
  file_table[FD_FB].size = width * height;
}
