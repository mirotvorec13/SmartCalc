#ifndef S21_CALC_H
#define S21_CALC_H

#include <stdbool.h>

typedef struct s21_coords {
  int count;
  double *x;
  double *y;
} s21_coords;

typedef struct s21_calc_result {
  double result;
  bool error;
} s21_calc_result;

typedef struct s21_calc_range_result {
  s21_coords coords;
  int max_y;
  bool error;
} s21_calc_range_result;

typedef struct s21_paymant {
  double debt;
  double percent;
  double total;
  double remains;
} s21_payment;

typedef struct s21_paymants {
  int count;
  double total_percent;
  s21_payment *payment;
} s21_payments;

s21_calc_result s21_calc(char *str);
s21_calc_result s21_calc_x(char *str, double x);
s21_calc_range_result s21_calc_range(char *str, int from, int to, double step);

void s21_free_coords(s21_coords *coords);

s21_payments *s21_credit_annuent(int sum, int months, int rate);
s21_payments *s21_credit_diff(int sum, int months, int rate);
void s21_payments_free(s21_payments *payments);

#endif
