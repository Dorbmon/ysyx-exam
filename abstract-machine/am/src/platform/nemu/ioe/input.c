#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000
void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint16_t high   = inw(0xa0000062);
  uint16_t nowKey = inw(0xa0000060);
  if (high == 0xF0) {
    kbd->keydown = 0;
  } else {
    kbd->keydown = 1;
  }
  kbd->keycode = nowKey;
}
