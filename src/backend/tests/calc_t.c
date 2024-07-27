#include <check.h>

#include "../s21_calc.h"
#include "s21_tests.h"

START_TEST(s21_calc1) {
  // arrange
  char *str = "2+2";
  double need_result = 4.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc2) {
  // arrange
  char *str = "-2+4";
  double need_result = 2.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc3) {
  // arrange
  char *str = "+2+2";
  double need_result = 4.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc4) {
  // arrange
  char *str = "2*(3-2)";
  double need_result = 1.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_x1) {
  // arrange
  char *str = "2+x";
  double x = 3.5;

  double need_result = 5.5;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc_x(str, x);

  // assert
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_x2) {
  // arrange
  char *str = "sin(x)";
  double x = 1.0;

  double need_result = 0.84147098481;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc_x(str, x);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_range1) {
  // arrange
  char *str = "2*x";
  int from = -1;
  int to = 1;
  double step = 0.1;

  const int need_result_count = 21;
  double need_result_x[] = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4,
                            -0.3, -0.2, -0.1, 0.0,  0.1,  0.2,  0.3,
                            0.4,  0.5,  0.6,  0.7,  0.8,  0.9,  1.0};
  double need_result_y[] = {-2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.8,
                            -0.6, -0.4, -0.2, 0.0,  0.2,  0.4,  0.6,
                            0.8,  1.0,  1.2,  1.4,  1.6,  1.8,  2.0};
  double need_result_error = false;

  // act
  s21_calc_range_result result = s21_calc_range(str, from, to, step);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_int_eq(result.coords.count, need_result_count);

  for (int i = 0; i < need_result_count; i++) {
    ck_assert_double_eq_tol(result.coords.x[i], need_result_x[i], S21_TOL);
    ck_assert_double_eq_tol(result.coords.y[i], need_result_y[i], S21_TOL);
  }

  s21_free_coords(&result.coords);
}
END_TEST

START_TEST(s21_calc_err1) {
  // arrange
  char *str = "d";
  double need_result_error = true;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_err2) {
  // arrange
  char *str = "2+";
  double need_result_error = true;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_err3) {
  // arrange
  char *str = "2+()";
  double need_result_error = true;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_err4) {
  // arrange
  char *str = ")";
  double need_result_error = true;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_x_err1) {
  // arrange
  char *str = "d";
  double need_result_error = true;

  // act
  s21_calc_result result = s21_calc_x(str, 0.0);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST
START_TEST(s21_calc_range_err1) {
  // arrange
  char *str = "2+";
  double need_result_error = true;

  // act
  s21_calc_range_result result = s21_calc_range(str, 0.0, 0.0, 0);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_range_err2) {
  // arrange
  char *str = "2+2";
  int out_range = 10000000;
  double need_result_error = true;

  // act
  s21_calc_range_result result = s21_calc_range(str, 0.0, out_range, 0);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_range_err3) {
  // arrange
  char *str = "2+2";
  int out_range = -10000000;
  double need_result_error = true;

  // act
  s21_calc_range_result result = s21_calc_range(str, out_range, 0.0, 0);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
}
END_TEST

START_TEST(s21_calc_funcs1) {
  // arrange
  char *str = "sin(0.5)";
  double need_result = 0.479425538604203;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs2) {
  // arrange
  char *str = "cos(0.5)";
  double need_result = 0.8775825618903728;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs3) {
  // arrange
  char *str = "tan(0.5)";
  double need_result = 0.5463024898437905;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs4) {
  // arrange
  char *str = "asin(0.5)";
  double need_result = 0.5235987755982989;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs5) {
  // arrange
  char *str = "acos(0.5)";
  double need_result = 1.0471975511965979;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs6) {
  // arrange
  char *str = "atan(0.5)";
  double need_result = 0.4636476090008061;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs7) {
  // arrange
  char *str = "sqrt(0.5)";
  double need_result = 0.7071067811865476;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs8) {
  // arrange
  char *str = "ln(0.5)";
  double need_result = -0.69314718056;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs9) {
  // arrange
  char *str = "log(0.5)";
  double need_result = -0.30102999566;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs10) {
  // arrange
  char *str = "0.5^2";
  double need_result = 0.25;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs11) {
  // arrange
  char *str = "11.5 mod 2.5";
  double need_result = 1.5;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs12) {
  // arrange
  char *str = "5-11";
  double need_result = -6.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs13) {
  // arrange
  char *str = "-6.0 + 11";
  double need_result = 5.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs14) {
  // arrange
  char *str = "-6.0 * 11";
  double need_result = -66.0;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

START_TEST(s21_calc_funcs15) {
  // arrange
  char *str = "-6.0 / 11";
  double need_result = -0.54545454545;
  double need_result_error = false;

  // act
  s21_calc_result result = s21_calc(str);

  // assert
  ck_assert_int_eq(result.error, need_result_error);
  ck_assert_ldouble_ge_tol(result.result, need_result, S21_TOL);
}
END_TEST

Suite *calc_sc(void) {
  Suite *suite = suite_create("s21_calc");

  TCase *oper_list_tc = tcase_create("oper_list");
  tcase_add_test(oper_list_tc, s21_calc1);
  tcase_add_test(oper_list_tc, s21_calc2);
  tcase_add_test(oper_list_tc, s21_calc3);
  tcase_add_test(oper_list_tc, s21_calc4);
  tcase_add_test(oper_list_tc, s21_calc_x1);
  tcase_add_test(oper_list_tc, s21_calc_x2);
  tcase_add_test(oper_list_tc, s21_calc_range1);

  tcase_add_test(oper_list_tc, s21_calc_err1);
  tcase_add_test(oper_list_tc, s21_calc_err2);
  tcase_add_test(oper_list_tc, s21_calc_err3);
  tcase_add_test(oper_list_tc, s21_calc_err4);
  tcase_add_test(oper_list_tc, s21_calc_x_err1);
  tcase_add_test(oper_list_tc, s21_calc_range_err1);
  tcase_add_test(oper_list_tc, s21_calc_range_err2);
  tcase_add_test(oper_list_tc, s21_calc_range_err3);

  tcase_add_test(oper_list_tc, s21_calc_funcs1);
  tcase_add_test(oper_list_tc, s21_calc_funcs2);
  tcase_add_test(oper_list_tc, s21_calc_funcs3);
  tcase_add_test(oper_list_tc, s21_calc_funcs4);
  tcase_add_test(oper_list_tc, s21_calc_funcs5);
  tcase_add_test(oper_list_tc, s21_calc_funcs6);
  tcase_add_test(oper_list_tc, s21_calc_funcs7);
  tcase_add_test(oper_list_tc, s21_calc_funcs8);
  tcase_add_test(oper_list_tc, s21_calc_funcs9);
  tcase_add_test(oper_list_tc, s21_calc_funcs10);
  tcase_add_test(oper_list_tc, s21_calc_funcs11);
  tcase_add_test(oper_list_tc, s21_calc_funcs12);
  tcase_add_test(oper_list_tc, s21_calc_funcs13);
  tcase_add_test(oper_list_tc, s21_calc_funcs14);
  tcase_add_test(oper_list_tc, s21_calc_funcs15);
  suite_add_tcase(suite, oper_list_tc);

  return suite;
}

MAKE_TEST(calc)
