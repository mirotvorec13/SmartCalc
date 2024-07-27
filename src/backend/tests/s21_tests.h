#ifndef S21_TESTS_H
#define S21_TESTS_H

#define S21_TOL 1e-7

#define PRINT_MSG(msg) \
  (printf("\n\033[32m%s\033[39m\n\n\033[34m-------\n\033[39m", msg))

#define RUN_TEST(TEST_NAME) \
  s21_##TEST_NAME##_t();    \
  printf("\033[34m-------\n\033[39m");

#define MAKE_SRUNNER(SUITE_NAME)                          \
  SRunner *suite_runner = srunner_create(SUITE_NAME);     \
  srunner_set_fork_status(suite_runner, CK_NOFORK);       \
  srunner_run_all(suite_runner, CK_NORMAL);               \
  int failed_count = srunner_ntests_failed(suite_runner); \
  srunner_free(suite_runner);                             \
  return failed_count;

#define MAKE_TEST(TEST_NAME)         \
  int s21_##TEST_NAME##_t(void) {    \
    Suite *suite = TEST_NAME##_sc(); \
    MAKE_SRUNNER(suite)              \
  }

#define PROTOTYPE(TEST_NAME) int s21_##TEST_NAME##_t(void);

// Math
PROTOTYPE(struct_data)
PROTOTYPE(calc)
PROTOTYPE(credit)

#endif
