#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>
typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char order[100];
  word_t lastValue;

} WP;
WP* new_wp();
void free_wp(WP *wp);
word_t expr(char *e, bool *success);
bool checkCheckPoints();
#endif
