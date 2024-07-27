#define MAIN_CNT 1

#if MAIN_CNT == 1

#include <stdio.h>

#include "../s21_calc.h"

// void polish_deque_print_bottom(polish_deque *deque) {
//   if (deque == NULL || deque->bottom == NULL || deque->top == NULL) {
//     printf("ERROR\n");
//     return;
//   }
//
//   polish_node *tmp = deque->bottom;
//
//   while (tmp != NULL) {
//     if (tmp->operator!= NULL) {
//       printf("%s ", tmp->operator->oper_str);
//       printf("%d\n", tmp->operator->priority);
//     } else {
//       printf("%Lf\n", tmp->num);
//     }
//     tmp = tmp->next;
//   }
//   printf("\n");
// }

void print_paymants(const s21_payments *paymants) {
  for (int i = 0; i < paymants->count; i++) {
    printf("%d %.7f %.7f %.7f %.7f\n", i + 1, paymants->payment[i].debt,
           paymants->payment[i].percent, paymants->payment[i].total,
           paymants->payment[i].remains);
  }
  printf("total %.7f\n", paymants->total_percent);
}

int main(void) {
  // char *str =
  // "atan cos sin tan - tan tan cos   12.23 + 123.123123 111.111   sin ";
  // "2 - (3 - 1 * 4 + 9)";
  // "2 * (40 - sin(2 + 3) * 2 / 3) + 1 * x";
  // "0-1+(0-1)";
  // "2*(acos(14)+4-2)";
  // "(2-3)*2mod2";
  // "1/x";

  s21_payments *res = s21_credit_diff(200, 1000, 2);
  print_paymants(res);
  // s21_payments *res = credit_annuent(2000000, 60, 15);
  // print_paymants(res);
  s21_payments_free(res);

  // s21_polish_result res = s21_polish(str);

  // s21_calc_range_result res = s21_calc_range(str, -10, 10, 0.1);
  // for (int i = 0; i < res.coords.count; i++) {
  //   printf("%f %f\n", res.coords.x[i], res.coords.y[i]);
  // }
  //
  // printf("%d\n", res.coords.count);
  // s21_free_coords(&res.coords);
  //
  // s21_calc_result calc_res = s21_calc(str);
  // if (!calc_res.error) {
  //   printf("%f\n", calc_res.result);
  // } else {
  //   printf("ERROR\n");
  // }
  //
  return 0;
}

#endif
