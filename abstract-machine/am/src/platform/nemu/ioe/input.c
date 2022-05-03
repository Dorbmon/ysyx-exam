#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000
void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t high   = inl(0xa0000064);
  uint32_t nowKey = inl(0xa0000060);
  if (high == 0xF0) {
    kbd->keydown = 0;
  } else {
    kbd->keydown = 1;
  }
  kbd->keycode = nowKey;
}
