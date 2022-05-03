#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) { 
  static char buf [256];
  va_list args;
	va_start(args, fmt);
  int ret = vsprintf(buf, fmt, args);
  for (int i = 0;;++ i) {
    if (buf [i] != '\0') {
      putch(buf [i]);
    } else {
      break;
    }
  }
  return ret;
}
int isDigit(unsigned char c) {
  if (c >= '0' && c <= '9')
    return 1;
  else
    return 0;
}
void xtoa(unsigned int n, char *buf) {
  int i;
  if (n < 16) {
    if (n < 10) {
      buf[0] = n + '0';
    } else {
      buf[0] = n - 10 + 'a';
    }
    buf[1] = '\0';
    return;
  }
  xtoa(n / 16, buf);
  for (i = 0; buf[i] != '\0'; i++)
    ;

  if ((n % 16) < 10) {
    buf[i] = (n % 16) + '0';
  } else {
    buf[i] = (n % 16) - 10 + 'a';
  }
  buf[i + 1] = '\0';
}
void itoa(unsigned int n, char *buf) {
  int i;
  if (n < 10) {
    buf[0] = n + '0';
    buf[1] = '\0';
    return;
  }
  itoa(n / 10, buf);
  for (i = 0; buf[i] != '\0'; i++)
    ;
  buf[i] = (n % 10) + '0';
  buf[i + 1] = '\0';
}
int vsprintf(char *str, const char *fmt, va_list ap) {
  int count = 0;
  char c;
  char *s;
  int n;
  char buf[65];
  char digit[16];
  memset(buf, 0, sizeof(buf));
  memset(digit, 0, sizeof(digit));
  while (*fmt != '\0') {
    if (*fmt == '%') {
      fmt++;
      switch (*fmt) {
      case 'd': /*整型*/
      {
        n = va_arg(ap, int);
        if (n < 0) {
          *str = '-';
          str++;
          n = -n;
        }
        itoa(n, buf);
        memcpy(str, buf, strlen(buf));
        str += strlen(buf);
        ++ count;
        break;
      }
      case 'c': /*字符型*/
      {
        c = va_arg(ap, int);
        *(str++) = c;
        ++ count;
        break;
      }
      case 'x': /*16进制*/
      {
        n = va_arg(ap, int);
        xtoa(n, buf);
        memcpy(str, buf, strlen(buf));
        str += strlen(buf);
        ++ count;
        break;
      }
      case 's': /*字符串*/
      {
        s = va_arg(ap, char *);
        memcpy(str, s, strlen(s));
        str += strlen(s);
        ++ count;
        break;
      }
      case '%': /*输出%*/
      {
        *(str++) = '%';
        break;
      }
      }
    } else {
      *(str++) = *fmt;
    }
    fmt++;
  }
  return count;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}
int sprintf(char *str, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = vsprintf(str, fmt, ap);
  *str = '\0';
  va_end(ap);
  return ret;
}

#endif
