#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)
void __am_gpu_config(AM_GPU_CONFIG_T *cfg);
AM_GPU_CONFIG_T cfg;
void __am_gpu_init() {
  int i;
  __am_gpu_config(&cfg);
  int w = cfg.width;
  int h = cfg.height;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = i;
  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t sizeData = inl(VGACTL_ADDR);
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = (sizeData >> 16), .height = (sizeData & ((1 << 16) - 1)),
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  // 开始输出画面
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (int i = 0;i < ctl->h;++ i) {
    int y = i + ctl->y;
    for (int j = 0;j < ctl->w;++ j) {
      int x = j + ctl->x;
      fb [y * cfg.width + x] = ((uint32_t*)(ctl->pixels))[i * ctl->w + j];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
