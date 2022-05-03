#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000
void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  //uint16_t high   = inw(0xa0000062);
  uint32_t nowKey = inw(KBD_ADDR);
  kbd->keydown = (nowKey & KEYDOWN_MASK ? true : false);
  //kbd->keycode = nowKey & ((1 << 16) - 1);
  kbd->keycode = nowKey & ~KEYDOWN_MASK;
}
