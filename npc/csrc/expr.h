#ifndef EXPR_H
#define EXPR_H
#include "isa.h"
void init_regex();
uint32_t eval(int p, int q);
uint32_t expr(char *e, bool *success);
#endif