#include <am.h>

void __am_timer_init() {
}
#define inl(x) (*((uint32_t*)x))
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = 0;
  uptime->us = *(uint64_t*)(0xa0000048);//((uint64_t)inl(0xa0000048 + 0x4) << 32) + (uint64_t)inl(0xa0000048);
  //uptime->us = ((uint64_t)inl(0xa0000048 + 0x4) << 32) + (uint64_t)inl(0xa0000048);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
