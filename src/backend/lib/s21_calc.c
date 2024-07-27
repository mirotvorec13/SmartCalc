#include "../s21_calc.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "polish.h"
#include "struct_data/oper_list.h"
#include "struct_data/polish_deque.h"

typedef struct {
  polish_deque *deque;
  polish_deque *support;
  oper_list *operators;

  bool error;
} init_result;

static init_result init(char *str);
static double calculate(polish_deque *deque, polish_deque *support, double x);
static void init_result_free(init_result *ir);
double s21_get_max_y(s21_coords *coords);

s21_calc_result s21_calc(char *str) {
  s21_calc_result result = {0};
  init_result ir = init(str);

  if (!ir.error) {
    result.result = calculate(ir.deque, ir.support, 0.0);
  } else {
    result.error = true;
  }

  init_result_free(&ir);

  return result;
}

s21_calc_result s21_calc_x(char *str, double x) {
  s21_calc_result result = {0};
  init_result ir = init(str);
  if (!ir.error) {
    result.result = calculate(ir.deque, ir.support, x);
  } else {
    result.error = true;
  }

  init_result_free(&ir);

  return result;
}

s21_calc_range_result s21_calc_range(char *str, int from, int to, double step) {
  if (from < -1000000 || to > 1000000) {
    return (s21_calc_range_result){.max_y = 0.0, .error = true};
  }

  init_result ir = init(str);
  s21_calc_range_result result = {0};

  if (!ir.error) {
    result.coords.count = ((to - from) / step) + 1;
    result.coords.x = (double *)malloc(result.coords.count * sizeof(double));
    result.coords.y = (double *)malloc(result.coords.count * sizeof(double));

  } else {
    result.error = true;
  }

  if (result.coords.x == NULL || result.coords.y == NULL) {
    result.coords.count = 0;
    result.coords.x = NULL;
    result.coords.y = NULL;
    result.error = true;
  } else {
    double x = from;
    for (int i = 0; i < result.coords.count; i++, x += step) {
      if (x > -0.0001 && x < 0.0001) {
        x = 0.0;
      }

      double y = calculate(ir.deque, ir.support, x);
      if (y != INFINITY && y != -INFINITY && y == y) {
        result.coords.x[i] = x;
        result.coords.y[i] = y;
      } else {
        result.coords.count--;
        i--;
      }
    }

    result.max_y = s21_get_max_y(&result.coords);
  }

  init_result_free(&ir);
  return result;
}

void s21_free_coords(s21_coords *coords) {
  free(coords->x);
  free(coords->y);
}

static init_result init(char *str) {
  init_result result = {0};
  result.operators = oper_list_create();

  if (result.operators) {
    polish_deque *lexems = parser(str, result.operators);

    if (lexems) {
      result.deque = make_polish(lexems);
      polish_deque_free(lexems);
    }

    if (result.deque) {
      result.support = polish_deque_create();
    }
  }

  if (!result.operators || !result.deque || !result.support) {
    result.error = true;
  }

  return result;
}

static void init_result_free(init_result *ir) {
  polish_deque_free(ir->deque);
  polish_deque_free(ir->support);
  oper_list_free(ir->operators);
}

static double calculate(polish_deque *deque, polish_deque *support, double x) {
  polish_node *node = deque->bottom;

  while (node) {
    if (node->operator&& node->operator->priority != IS_X) {
      if (node->operator->args_count == 1) {
        double xtmp = polish_deque_pop(support);
        xtmp = node->operator->func_one_arg(xtmp);
        polish_deque_push_num(support, xtmp);
      } else {
        double y = polish_deque_pop(support);
        double xtmp = polish_deque_pop(support);
        xtmp = node->operator->func_two_arg(xtmp, y);
        polish_deque_push_num(support, xtmp);
      }
    } else {
      double num = node->num;
      if (node->operator&& node->operator->priority == IS_X) {
        num = x;
      }
      polish_deque_push_num(support, num);
    }
    node = node->next;
  }

  return polish_deque_pop(support);
}

double s21_get_max_y(s21_coords *coords) {
  double max_y = 0.0;

  for (int i = 0; i < coords->count; i++) {
    double y = coords->y[i];
    if (y < 0) {
      y = -y;
    }
    if (y > max_y) {
      max_y = y;
    }
  }

  return max_y;
}
