#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

word_t expr(char *e, bool *success);


typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char expr[32];
  /* TODO: Add more members if necessary */

} WP;

WP* new_wp();
void free_wp(int no);
bool check_watchpoint();
void watchpoint_display();

#endif
