#include "s21_tests.h"

#include <stdio.h>

static void print_head(void);

int main(void) {
  print_head();

  // Math
  PRINT_MSG("STRUCT DATA");
  RUN_TEST(struct_data);

  PRINT_MSG("CALC");
  RUN_TEST(calc);

  PRINT_MSG("CREDIT");
  RUN_TEST(credit);

  printf("\n");
  return 0;
}

static void print_head(void) {
  printf(
      "\033[34m****************************************************************"
      "*******"
      "\n\033["
      "39m");
  printf("\033[34m***\033[39m Тесты SmartCalc \033[34m***\033[39m\n");
  printf(
      "\033[34m****************************************************************"
      "*******"
      "\n\n\033["
      "39m");
}
