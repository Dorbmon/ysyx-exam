#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) { panic("Not implemented"); }
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
int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}
int sprintf(char *str, const char *fmt, ...) {
  int count = 0;
  char c;
  char *s;
  int n;
  int index = 0;
  int ret = 2;
  char buf[65];
  char digit[16];
  int num = 0;
  int len = 0;
  memset(buf, 0, sizeof(buf));
  memset(digit, 0, sizeof(digit));
  va_list ap;
  va_start(ap, fmt);
  while (*fmt != '\0') {
    printf("*fmt=[%c]\n", *fmt);
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
        break;
      }
      case 'c': /*字符型*/
      {
        c = va_arg(ap, int);
        *str = c;
        str++;

        break;
      }
      case 'x': /*16进制*/
      {
        n = va_arg(ap, int);
        xtoa(n, buf);
        memcpy(str, buf, strlen(buf));
        str += strlen(buf);
        break;
      }
      case 's': /*字符串*/
      {
        s = va_arg(ap, char *);
        memcpy(str, s, strlen(s));
        str += strlen(s);
        break;
      }
      case '%': /*输出%*/
      {
        *str = '%';
        str++;

        break;
      }
      case '0': /*位不足的左补0*/
      {
        index = 0;
        num = 0;
        memset(digit, 0, sizeof(digit));

        while (1) {
          fmt++;
          ret = isDigit(*fmt);
          if (ret == 1) //是数字
          {
            digit[index] = *fmt;
            index++;
          } else {
            num = atoi(digit);
            break;
          }
        }
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
          len = strlen(buf);
          if (len >= num) {
            memcpy(str, buf, strlen(buf));
            str += strlen(buf);
          } else {
            memset(str, '0', num - len);
            str += num - len;
            memcpy(str, buf, strlen(buf));
            str += strlen(buf);
          }
          break;
        }
        case 'x': /*16进制*/
        {
          n = va_arg(ap, int);
          xtoa(n, buf);
          len = strlen(buf);
          if (len >= num) {
            memcpy(str, buf, len);
            str += len;
          } else {
            memset(str, '0', num - len);
            str += num - len;
            memcpy(str, buf, len);
            str += len;
          }
          break;
        }
        case 's': /*字符串*/
        {
          s = va_arg(ap, char *);
          len = strlen(s);
          if (len >= num) {
            memcpy(str, s, strlen(s));
            str += strlen(s);
          } else {
            memset(str, '0', num - len);
            str += num - len;
            memcpy(str, s, strlen(s));
            str += strlen(s);
          }
          break;
        }
        default:
          break;
        }
      }
      default:
        break;
      }
    } else {
      *str = *fmt;
      str++;

      if (*fmt == '\n') {
      }
    }
    fmt++;
  }

  va_end(ap);

  return count;
}

#endif
