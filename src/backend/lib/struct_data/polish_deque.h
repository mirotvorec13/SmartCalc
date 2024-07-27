#ifndef S21_POLISH_DEQUE_H
#define S21_POLISH_DEQUE_H

#include "oper_list.h"

typedef struct polish_node {
  oper_node *operator;
  double num;

  struct polish_node *next;
  struct polish_node *prev;
} polish_node;

typedef struct polish_deque {
  polish_node *top;
  polish_node *bottom;
} polish_deque;

polish_deque *polish_deque_create();
void polish_deque_free(polish_deque *deque);

polish_node *polish_node_create(oper_node *operator, double value);

void polish_deque_push_oper(polish_deque *deque, oper_node *operator);
void polish_deque_push_num(polish_deque *deque, double num);
double polish_deque_pop(polish_deque *deque);
void polish_deque_top_delete(polish_deque *deque);

#endif
