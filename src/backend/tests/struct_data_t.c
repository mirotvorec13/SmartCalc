#include <check.h>

#include "../lib/struct_data/oper_list.h"
#include "../lib/struct_data/polish_deque.h"
#include "s21_tests.h"

START_TEST(oper_list_create_test) {
  // arrange

  // act
  oper_list *result = oper_list_create();

  // assert
  ck_assert_ptr_nonnull(result);
  ck_assert_ptr_nonnull(result->start);
  ck_assert_ptr_nonnull(result->end);

  oper_list_free(result);
}
END_TEST

START_TEST(oper_list_free_null) {
  // arrange
  oper_list operators = {0};

  // act
  oper_list_free(NULL);
  oper_list_free(&operators);

  // assert
}
END_TEST

START_TEST(oper_list_find_equal) {
  // arrange
  oper_list *operators = oper_list_create();
  char *str = "sin";

  // act
  oper_node *result = oper_list_find(operators, &str);

  // assert
  ck_assert_pstr_eq(result->oper_str, "sin");
  ck_assert_pstr_eq(str, "");

  oper_list_free(operators);
}
END_TEST

START_TEST(oper_list_find_space) {
  // arrange
  oper_list *operators = oper_list_create();
  char *str = " sin ";

  // act
  oper_node *result = oper_list_find(operators, &str);

  // assert
  ck_assert_pstr_eq(result->oper_str, "sin");
  ck_assert_pstr_eq(str, " ");

  oper_list_free(operators);
}
END_TEST

START_TEST(oper_list_find_not_equal) {
  // arrange
  oper_list *operators = oper_list_create();
  char *str = "sdf";

  // act
  oper_node *result = oper_list_find(operators, &str);

  // assert
  ck_assert_ptr_null(result);
  ck_assert_pstr_eq(str, "sdf");

  oper_list_free(operators);
}
END_TEST

START_TEST(oper_list_find_null) {
  // arrange
  oper_list operators = {.start = (oper_node *)1, .end = (oper_node *)1};
  oper_list operators_null = {0};
  char *str = NULL;

  // act
  oper_node *result1 = oper_list_find(NULL, &str);
  oper_node *result2 = oper_list_find(&operators_null, &str);
  oper_node *result3 = oper_list_find(&operators, NULL);
  oper_node *result4 = oper_list_find(&operators, &str);

  // assert
  ck_assert_ptr_null(result1);
  ck_assert_ptr_null(result2);
  ck_assert_ptr_null(result3);
  ck_assert_ptr_null(result4);
}
END_TEST

START_TEST(polish_deque_push_oper_null) {
  // arrange
  oper_node operators = {.next = (oper_node *)1};
  polish_deque *deque = polish_deque_create();

  // act
  polish_deque_push_oper(NULL, &operators);
  polish_deque_push_oper(deque, NULL);

  // assert

  polish_deque_free(deque);
}
END_TEST

START_TEST(polish_deque_push_num_null) {
  // arrange

  // act
  polish_deque_push_num(NULL, 0.0);

  // assert
}
END_TEST

START_TEST(polish_deque_pop_null) {
  // arrange
  polish_deque *deque = polish_deque_create();

  // act
  polish_deque_pop(NULL);
  polish_deque_pop(deque);

  // assert

  polish_deque_free(deque);
}
END_TEST

START_TEST(polish_deque_top_delete_null) {
  // arrange
  polish_deque *deque = polish_deque_create();

  // act
  polish_deque_top_delete(NULL);
  polish_deque_top_delete(deque);

  // assert

  polish_deque_free(deque);
}
END_TEST

Suite *struct_data_sc(void) {
  Suite *suite = suite_create("struct_data");

  TCase *oper_list_tc = tcase_create("oper_list");
  tcase_add_test(oper_list_tc, oper_list_create_test);
  tcase_add_test(oper_list_tc, oper_list_free_null);
  tcase_add_test(oper_list_tc, oper_list_find_equal);
  tcase_add_test(oper_list_tc, oper_list_find_space);
  tcase_add_test(oper_list_tc, oper_list_find_not_equal);

  tcase_add_test(oper_list_tc, oper_list_find_null);
  tcase_add_test(oper_list_tc, polish_deque_push_oper_null);
  tcase_add_test(oper_list_tc, polish_deque_push_num_null);
  tcase_add_test(oper_list_tc, polish_deque_pop_null);
  tcase_add_test(oper_list_tc, polish_deque_top_delete_null);
  suite_add_tcase(suite, oper_list_tc);

  return suite;
}

MAKE_TEST(struct_data)
