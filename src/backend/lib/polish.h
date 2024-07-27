
#ifndef POLISH_H
#define POLISH_H

#include "struct_data/polish_deque.h"

polish_deque *parser(char *str, oper_list *operators);
polish_deque *make_polish(polish_deque *lexems);

double s21_sin(double x);
double s21_cos(double x);
double s21_tan(double x);
double s21_asin(double x);
double s21_acos(double x);
double s21_atan(double x);
double s21_sqrt(double x);
double s21_ln(double x);
double s21_log(double x);
double s21_pow(double x, double y);
double s21_mod(double x, double y);
double s21_sub(double x, double y);
double s21_add(double x, double y);
double s21_mult(double x, double y);
double s21_div(double x, double y);

#endif
