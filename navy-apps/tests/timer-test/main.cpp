#include <stdio.h>

#include <sys/time.h>

int main() {
  struct timeval tv, last;
  struct timezone tz;
  gettimeofday(&last, &tz);
  while (1) {
    gettimeofday(&tv, &tz);
    if (tv.tv_usec - last.tv_usec > 500000) {
      printf("after 0.5 second...\n");
      last = tv;
    }
  }
  return 0;
}
