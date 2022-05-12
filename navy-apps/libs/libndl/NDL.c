#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int real_w, real_h;
uint32_t NDL_GetTicks() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return tv.tv_usec;
}

int NDL_PollEvent(char *buf, int len) {
  FILE *fp = fopen("/dev/events", "r+");
  return fread(buf, len, 1, fp);
}

void NDL_OpenCanvas(int *w, int *h) {
  if (*w == 0 && *h == 0) { 
    *w = real_w;*h = real_h;
  }
  screen_w = *w; screen_h = *h;
  if (getenv("NWM_APP")) {
    int fbctl = 4;
    fbdev = 5;
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  FILE* fd = fopen("/dev/fb", "w");
  for (int i = y;i < y + h && i < real_h;++ i) {
    fseek(fd, i * real_w + x, SEEK_SET);
    size_t len = w * sizeof(uint32_t);
    if (x + w > screen_w) {
      //len = (screen_w - x) * sizeof(uint32_t);
    }
    printf("bf:%d\n", (i * real_w + x));
    fwrite(pixels + (i - y) * w, len, 1, fd);
    printf("out\n");
  }
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  FILE* dispInfo = fopen("/proc/dispinfo", "r+");
  static char buf [64];
  fread(buf, sizeof(buf), 1, dispInfo);
  sscanf(buf, "WIDTH:%d\nHEIGHT:%d", &real_w, &real_h);
  return 0;
}

void NDL_Quit() {
}
