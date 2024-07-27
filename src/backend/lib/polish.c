#include <stdbool.h>
#include <stdlib.h>

#include "struct_data/polish_deque.h"

static bool priority_handler(polish_deque *result, polish_deque *support,
                             int priority);
static bool check_polish(polish_deque *deque);

polish_deque *make_polish(polish_deque *lexems) {
  polish_deque *result = polish_deque_create();
  polish_deque *support = polish_deque_create();
  polish_node *node = lexems->bottom;

  bool un_minus = true;
  bool err = false;

  while (node && !err) {
    if (node->operator) {
      if (node->operator->priority == BRACKET_CLOSE &&(
              !node->prev ||
              (node->prev->operator&& node->prev->operator->priority ==
               BRACKET_OPEN))) {
        err = true;
        continue;
      }
      if (un_minus && ((node->operator->oper_str[0] == '-') ||
                       (node->operator->oper_str[0] == '+'))) {
        polish_deque_push_num(result, 0);
      }
      err = !priority_handler(result, support, node->operator->priority);
      if (err) {
        continue;
      }
      if (node->operator->priority != BRACKET_CLOSE) {
        polish_deque_push_oper(support, node->operator);
      }
      un_minus = node->operator->priority == BRACKET_OPEN;
    } else {
      polish_deque_push_num(result, node->num);
      un_minus = false;
    }
    node = node->next;
  }

  err |= !priority_handler(result, support, -1);
  err |= !check_polish(result);
  err |= support->top != NULL;

  if (err) {
    polish_deque_free(result);
    result = NULL;
  }
  polish_deque_free(support);

  return result;
}

static bool priority_handler(polish_deque *result, polish_deque *support,
                             int priority) {
  if (priority == BRACKET_OPEN) {
    return true;
  }

  bool res = true;

  polish_node *sup_node = support->top;
  while (sup_node && sup_node->operator->priority >= priority) {
    polish_deque_push_oper(result, sup_node->operator);
    polish_deque_top_delete(support);
    sup_node = support->top;
  }

  if (priority == BRACKET_CLOSE) {
    if (sup_node && sup_node->operator->priority == BRACKET_OPEN) {
      polish_deque_top_delete(support);
      if (support->top && support->top->operator->args_count == 1) {
        polish_deque_push_oper(result, support->top->operator);
        polish_deque_top_delete(support);
      }
    } else {
      res = false;
    }
  }

  return res;
}

static bool check_polish(polish_deque *deque) {
  polish_node *node = deque->bottom;
  bool result = true;
  int nums_cnt = 0;

  while (node && result) {
    if (node->operator) {
      if (node->operator->priority == BRACKET_OPEN) {
        result = false;
        continue;
      }
      nums_cnt -= node->operator->args_count;
      if (nums_cnt < 0) {
        result = false;
      }
      nums_cnt++;
    } else {
      nums_cnt++;
    }
    node = node->next;
  }

  if (nums_cnt > 1) {
    result = false;
  }

  return result;
}
