#include "polish_deque.h"

#include <stdlib.h>

static void polish_deque_push_top(polish_deque *deque, oper_node *operator,
                                  double num);

polish_deque *polish_deque_create() {
  polish_deque *deque = (polish_deque *)malloc(sizeof(polish_deque));

  if (deque != NULL) {
    deque->bottom = NULL;
    deque->top = NULL;
  }

  return deque;
}

void polish_deque_free(polish_deque *deque) {
  if (deque == NULL) {
    return;
  }

  while (deque->top) {
    polish_node *node = deque->top;
    deque->top = deque->top->prev;
    free(node);
  }
  free(deque);
}

polish_node *polish_node_create(oper_node *operator, double num) {
  polish_node *pnode = (polish_node *)malloc(sizeof(polish_node));

  if (pnode != NULL) {
    pnode->operator= operator;
    pnode->num = num;
    pnode->next = NULL;
    pnode->prev = NULL;
  }

  return pnode;
}

void polish_deque_push_oper(polish_deque *deque, oper_node *operator) {
  if (!operator) {
    return;
  }
  polish_deque_push_top(deque, operator, 0.0L);
}

void polish_deque_push_num(polish_deque *deque, double num) {
  polish_deque_push_top(deque, NULL, num);
}

void polish_deque_top_delete(polish_deque *deque) {
  if (!deque || !deque->top) {
    return;
  }

  polish_node *node = deque->top;
  deque->top = deque->top->prev;
  if (deque->top == NULL) {
    deque->bottom = NULL;
  }
  free(node);
}

double polish_deque_pop(polish_deque *deque) {
  if (!deque || !deque->top) {
    return 0.0L;
  }

  double num = deque->top->num;
  polish_deque_top_delete(deque);

  return num;
}

static void polish_deque_push_top(polish_deque *deque, oper_node *operator,
                                  double num) {
  if (deque == NULL) {
    return;
  }

  polish_node *node = polish_node_create(operator, num);

  if (node != NULL) {
    if (deque->top == NULL) {
      deque->bottom = node;
      deque->top = node;
    } else {
      node->prev = deque->top;
      deque->top->next = node;
      deque->top = node;
    }
  }
}
