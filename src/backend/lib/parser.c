#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct_data/polish_deque.h"

static bool parse(char **str, polish_deque *pdeque, oper_list *operators);

polish_deque *parser(char *str, oper_list *operators) {
  polish_deque *pdeque = polish_deque_create();

  if (pdeque != NULL) {
    bool err = false;
    while (*str != '\0' && !err) {
      err = parse(&str, pdeque, operators);
    }
    if (err) {
      // TODO: Сделать освобождение памяти
      free(pdeque);
      pdeque = NULL;
    }
  }

  return pdeque;
}

static bool parse(char **str, polish_deque *pdeque, oper_list *operators) {
  bool result = false;

  oper_node *node = oper_list_find(operators, str);
  if (node) {
    polish_deque_push_oper(pdeque, node);
    while (**str == ' ') {
      (*str)++;
    }
  } else {
    double num = 0;
    int read_cnt = 0;
    sscanf(*str, "%lf %n", &num, &read_cnt);

    if (read_cnt > 0) {
      polish_deque_push_num(pdeque, num);
      *str += read_cnt;
    } else {
      result = true;
    }
  }

  return result;
}
