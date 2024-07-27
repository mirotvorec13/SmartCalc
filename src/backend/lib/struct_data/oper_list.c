#include "oper_list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../polish.h"

static bool oper_list_push(oper_list *list, char *oper_str, int priority,
                           int args_count, double (*func_one_arg)(double x),
                           double (*func_two_arg)(double x, double y));
static char *compare(char *string, char *substring);

static bool oper_list_init(oper_list *list) {
  bool result = true;

  result &= oper_list_push(list, "sin", 5, 1, s21_sin, NULL);
  result &= oper_list_push(list, "cos", 5, 1, s21_cos, NULL);
  result &= oper_list_push(list, "tan", 5, 1, s21_tan, NULL);
  result &= oper_list_push(list, "asin", 5, 1, s21_asin, NULL);
  result &= oper_list_push(list, "acos", 5, 1, s21_acos, NULL);
  result &= oper_list_push(list, "atan", 5, 1, s21_atan, NULL);
  result &= oper_list_push(list, "sqrt", 5, 1, s21_sqrt, NULL);
  result &= oper_list_push(list, "ln", 5, 1, s21_ln, NULL);
  result &= oper_list_push(list, "log", 5, 1, s21_log, NULL);

  result &= oper_list_push(list, "^", 4, 2, NULL, s21_pow);
  result &= oper_list_push(list, "mod", 3, 2, NULL, s21_mod);
  result &= oper_list_push(list, "-", 2, 2, NULL, s21_sub);
  result &= oper_list_push(list, "+", 2, 2, NULL, s21_add);
  result &= oper_list_push(list, "*", 3, 2, NULL, s21_mult);
  result &= oper_list_push(list, "/", 3, 2, NULL, s21_div);

  result &= oper_list_push(list, "x", IS_X, 0, NULL, NULL);
  result &= oper_list_push(list, "(", BRACKET_OPEN, 0, NULL, NULL);
  result &= oper_list_push(list, ")", BRACKET_CLOSE, 0, NULL, NULL);

  return result;
}

oper_list *oper_list_create() {
  oper_list *list = (oper_list *)malloc(sizeof(oper_list));

  if (list) {
    list->start = NULL;
    list->end = NULL;
    if (!oper_list_init(list)) {
      oper_list_free(list);
      list = NULL;
    }
  }

  return list;
}

void oper_list_free(oper_list *list) {
  if (!list || !list->start) {
    return;
  }

  while (list->start) {
    oper_node *node = list->start;
    list->start = list->start->next;
    free(node);
  }

  free(list);
}

oper_node *oper_list_find(oper_list *list, char **oper_str) {
  if (!list || !list->start || !oper_str || !(*oper_str)) {
    return NULL;
  }

  oper_node *node = list->start;

  bool found = false;
  while (node != NULL && !found) {
    char *op_str_find = compare(*oper_str, node->oper_str);
    if (op_str_find) {
      *oper_str = op_str_find;
      found = true;  // break
    } else {
      node = node->next;
    }
  }

  return node;
}

static bool oper_list_push(oper_list *list, char *oper_str, int priority,
                           int args_count, double (*func_one_arg)(double x),
                           double (*func_two_arg)(double x, double y)) {
  bool result = true;
  oper_node *node = (oper_node *)malloc(sizeof(oper_node));

  if (node) {
    node->oper_str = oper_str;
    node->priority = priority;
    node->args_count = args_count;
    node->func_one_arg = func_one_arg;
    node->func_two_arg = func_two_arg;
    node->next = NULL;

    if (list->start == NULL) {
      list->start = node;
      list->end = node;
    } else {
      list->end->next = node;
      list->end = node;
    }
  } else {
    result = false;
  }

  return result;
}

static char *compare(char *string, char *substring) {
  char *result = NULL;
  bool is_equal = true;

  while (*substring != '\0' && is_equal) {
    if (*string == ' ') {
      string++;
      continue;
    }
    if (*string++ != *substring++) {
      is_equal = false;
    }
  }

  if (is_equal) {
    result = string;
  }

  return result;
}
