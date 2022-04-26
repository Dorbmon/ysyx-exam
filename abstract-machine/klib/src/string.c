#include <klib-macros.h>
#include <klib.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  for (size_t i = 0;; i++) {
    if (s[i] == '\0')
      return i;
  }
}

char *strcpy(char *dst, const char *src) {
  char *res = dst;
  while ((*(dst++) = *(src++)) != '\0')
    ;
  return res;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  size_t i = 0;
  while (dst[i] != '\0')
    ++i;
  while (*src != '\0')
    dst[i++] = *(src++);
  dst[i] = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  size_t l1 = strlen(s1), l2 = strlen(s2);
  if (l1 != l2) {
    return l1 - l2;
  }
  for (size_t index = 0; index < l1; ++index) {
    if (s1[index] != s2[index])
      return s1[index] - s2[index];
  }
  return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  char *cs = (char *)s; // 一个字节一个字节赋值
  for (int i = 0; i < n; i++) {
    cs[i] = c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  char *ci = (char *)out; // 一个字节一个字节赋值
  char *co = (char *)in;
  for (int i = 0; i < n; i++) {
    ci[i] = co[i];
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  char *cs1 = (char *)s1;
  char *cs2 = (char *)s2;
  for (int i = 0; i < n; i++) {
    if (cs1[i] != cs2[i])
      return cs1[i] - cs2[i];
  }
  return 0;
}

#endif
