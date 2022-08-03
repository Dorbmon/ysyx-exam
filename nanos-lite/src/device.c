#include <common.h>
#include <string.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  for (int i = 0;i < len;++ i) {
    putch(*((uint8_t*)(buf) + i));
  }
  return len;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  const char* fmt = "WIDTH:%d\nHEIGHT:%d";
  sprintf(buf, fmt, io_read(AM_GPU_CONFIG).width, io_read(AM_GPU_CONFIG).height);
  return len;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  int width = io_read(AM_GPU_CONFIG).width;
  offset >>= 2;
  int y = offset / width;
  int x = offset - y * width;
  io_write(AM_GPU_FBDRAW, x, y, (uint32_t*)buf, len >> 2, 1, true);
  return len;
}
size_t events_read(void *buf, size_t offset, size_t len) {
  AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
  if (ev.keycode == AM_KEY_NONE) {
    return 0;
  }
  static char rbuf [50];
  if (ev.keydown) {
    strcpy(rbuf, "kd ");
  } else {
    strcpy(rbuf, "ku ");
  }
  strcat(rbuf, keyname[ev.keycode]);
  strcat(rbuf, "\n");
  //strcpy(buf, rbuf);
  size_t rlen = strlen(rbuf) + 1;
  //printf("rrr:%s\n", rbuf);
  memcpy(buf, rbuf, (rlen < len)?rlen:len);
  return len;
}
void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
