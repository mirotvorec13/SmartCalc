#include <check.h>

#include "../s21_calc.h"
#include "s21_tests.h"

START_TEST(s21_diff1) {
  // arrange
  int sum = 2000000;
  int term = 2;
  int percent = 20;

  // act
  s21_payments *result = s21_credit_diff(sum, term, percent);

  // assert
  ck_assert_int_eq(result->count, 2);
  ck_assert_double_eq_tol(result->payment->debt, 1000000.0, S21_TOL);
  ck_assert_double_eq_tol(result->payment->percent, 33879.7814208, S21_TOL);
  ck_assert_double_eq_tol(result->payment->remains, 1000000.0, S21_TOL);
  ck_assert_double_eq_tol(result->payment->total, 1033879.7814208, S21_TOL);
  ck_assert_double_eq_tol(result->total_percent, 50273.2240437, S21_TOL);

  s21_payments_free(result);
}
END_TEST

START_TEST(s21_diff2) {
  // arrange
  int sum = 2000000;
  int term = 60;
  int percent = 50;

  // act
  s21_payments *result = s21_credit_diff(sum, term, percent);

  // assert
  ck_assert_double_eq_tol(result->count, 60, S21_TOL);
  ck_assert_double_eq_tol(result->total_percent, 2542607.8548794, S21_TOL);

  s21_payments_free(result);
}
END_TEST

START_TEST(s21_diff3) {
  // arrange
  int sum = 200;
  int term = 1000;
  int percent = 2;

  // act
  s21_payments *result = s21_credit_diff(sum, term, percent);

  // assert
  ck_assert_double_eq_tol(result->count, 1000, S21_TOL);
  ck_assert_double_eq_tol(result->total_percent, 166.8365420, S21_TOL);

  s21_payments_free(result);
}
END_TEST

START_TEST(s21_annuent1) {
  // arrange
  int sum = 2000000;
  int term = 2;
  int percent = 20;

  // act
  s21_payments *result = s21_credit_annuent(sum, term, percent);

  // assert
  ck_assert_double_eq_tol(result->count, 2, S21_TOL);
  ck_assert_double_eq_tol(result->payment->debt, 991735.5371901, S21_TOL);
  ck_assert_double_eq_tol(result->payment->percent, 33333.3333333, S21_TOL);
  ck_assert_double_eq_tol(result->payment->total, 1025068.8705234, S21_TOL);
  ck_assert_double_eq_tol(result->payment->remains, 1008264.4628099, S21_TOL);
  ck_assert_double_eq_tol(result->total_percent, 50137.7410468, S21_TOL);

  s21_payments_free(result);
}
END_TEST

START_TEST(s21_annuent2) {
  // arrange
  int sum = 200;
  int term = 500;
  int percent = 2;

  // act
  s21_payments *result = s21_credit_annuent(sum, term, percent);

  // assert
  ck_assert_double_eq_tol(result->count, 500, S21_TOL);
  ck_assert_double_eq_tol(result->total_percent, 94.9329367, S21_TOL);

  s21_payments_free(result);
}
END_TEST

Suite *credit_sc(void) {
  Suite *suite = suite_create("s21_credit");

  TCase *credit_tc = tcase_create("credit");
  tcase_add_test(credit_tc, s21_diff1);
  tcase_add_test(credit_tc, s21_diff2);
  tcase_add_test(credit_tc, s21_diff3);
  tcase_add_test(credit_tc, s21_annuent1);
  tcase_add_test(credit_tc, s21_annuent2);
  suite_add_tcase(suite, credit_tc);

  return suite;
}

MAKE_TEST(credit)
