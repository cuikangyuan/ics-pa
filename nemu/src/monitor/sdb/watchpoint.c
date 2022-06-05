#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {0};
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

WP* new_wp() {
  WP* tmp_h = head, *tmp_f = free_;
  assert(tmp_f != NULL);
  if (tmp_h == NULL)
  {
    tmp_h = tmp_f;
    free_ = free_->next;
    tmp_f->next = NULL;
    head = tmp_h;
    return head;
  }
  while (tmp_h->next != NULL)
  {
    tmp_h = tmp_h->next;
  }
  tmp_h->next = tmp_f;
  free_ = tmp_f->next;
  tmp_f->next = NULL;
  return tmp_f;
}

void free_wp(int no) {
  WP* tmp = head;
  if (tmp != NULL && tmp->NO == no) 
  {
    head = head->next;
    tmp->next = free_;
    free_ = tmp;
    return;
  }

  bool is_found = false;
  while(tmp != NULL && tmp->next != NULL) {
    if (tmp->next->NO == no)
    {
      is_found = true;
      break;
    }
    tmp = tmp->next;
  }

  if (is_found == false)
  {
    printf("No such watchpoint.\n");
  } else {
    WP* tmp_h = tmp->next;
    tmp->next = tmp_h->next;
    tmp_h->next = free_;
    free_ = tmp_h;
  }
  
  
}

void watchpoint_display() {
  printf("%-15s%-15s\n\n", "NUM", "WHAT");
  WP* tmp = head;
  while (tmp != NULL)
  {
    printf("%-12d%-13s\n", tmp->NO, tmp->expr);
    tmp = tmp->next;
  }
  
}

bool check_watchpoint() {
  WP* tmp = head;
  bool success = false;
  bool ret = false;

  while (tmp != NULL)
  {
    int val = expr(tmp->expr, &success);
    if (success == true && val == 1)
    {
      printf("A watchpoint has been triggered\n");
      ret = true;
      break;
    }
    tmp = tmp->next;
    
  }
  
  return ret;
}
/* TODO: Implement the functionality of watchpoint */

