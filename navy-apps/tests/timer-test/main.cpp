#include <stdio.h>

#include <NDL.h>

int main() {
  NDL_Init(0);
  uint32_t t,last;
  last = NDL_GetTicks();
  while (1) {
    t = NDL_GetTicks();
    printf("%ld..\n", t);
    if (t - last > 500000) {
      printf("after 0.5 second...\n");
      last = t;
    }
  }
  return 0;
}
