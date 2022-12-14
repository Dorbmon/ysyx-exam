#include "sdb.h"
#include <string.h>
#define NR_WP 32



static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

WP* new_wp(char* order) {
  assert(free_ != NULL);
  WP* ret = free_;
  memcpy(ret->order, order, sizeof(char) * (strlen(order) + 1));
  bool success;
  ret->lastValue = expr(order, &success);
  assert(success);
  free_ = free_->next;
  if (head == NULL) {
    head = ret;
  } else {
    ret->next = head;
    head = ret;
  }
  return ret;
}
void free_wp(WP *wp) {
  if (free_ == NULL) {
    free_ = wp;
  } else {
    wp->next = free_;
    free_ = wp;
  }
  // 然后从原列表中删除
  if (wp == head) {
    head = wp->next;
    return;
  }
  for (WP* r = head;r != NULL;r = r->next) {
    if (r->next == wp) {
      r->next = wp->next;
      break;
    }
  }
}

bool checkCheckPoints() {
  for (WP* r = head;r != NULL;r = r->next) {
    bool success;
    word_t value = expr(r->order, &success);
    if (value != r->lastValue) {
      printf("check point:%d changed.It used to be %lx but now %lx\n", r->NO ,r->lastValue, value);
      r->lastValue = value;
      return true;
    }
  }
  return false;
}
void showCheckPoints() {
  for (WP* r = head;r != NULL;r = r->next) {
    printf("checkpoint %d,value:%lx, expr:%s\n",r->NO,r->lastValue,r->order);
  }
}
void removeCheckPoint(int id) {
  for (WP* r = head;r != NULL;r = r->next) {
    if (r->NO == id) {
      free_wp(r);
      return;
    }
  }
}