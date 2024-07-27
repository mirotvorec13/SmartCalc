#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../s21_calc.h"

typedef struct {
  double sum;
  int months;
  double rate;

  int curr_day;
  int curr_month;
  int curr_year;

  s21_payments *payments;
} args;

static int get_days_in_year(int year);
static int get_days_in_month(int month, int days_in_year);
static bool get_current_date(int *day, int *month, int *year);
static void calc_diff(args *args);

void s21_payments_free(s21_payments *payments) {
  free(payments->payment);
  free(payments);
}

s21_payments *s21_credit_annuent(int sum, int months, int rate) {
  /*
    Х = С * К
    где X — аннуитетный платеж,
    С — сумма кредита,
    К — коэффициент аннуитета.
    Коэффициент аннуитета считается так:
    К = (М * (1 + М) ^ S) / ((1 + М) ^ S — 1)
    где М — месячная процентная ставка по кредиту,
    S — срок кредита в месяцах.
    Допустим, вы берете в кредит 2 млн на 5 лет по ставке 15% годовых. Сначала
    подсчитаем коэффициент аннуитета.
    К = (0,0125 * (1 + 0,0125) ^ 60) / ((1 + 0,0125) ^ 60 — 1)
    Получаем коэффициент 0,02379.
    Подставляем значения в формулу:
    Х = 2 000 000 * К
    Получаем ежемесячный платеж, равный 47 580
    ₽.
  */
  s21_payments *payments = (s21_payments *)malloc(sizeof(s21_payments));
  if (payments) {
    payments->total_percent = 0;
    payments->payment = (s21_payment *)malloc(months * sizeof(s21_payment));
    if (payments->payment) {
      payments->count = months;
    } else {
      free(payments);
      payments = NULL;
    }
  }

  if (payments) {
    double rate_month = rate / 12.0 / 100;
    double remains = sum;
    double koef = (rate_month * pow((1 + rate_month), months)) /
                  (pow((1 + rate_month), months) - 1);
    double month_debt = sum * koef;

    for (int i = 0; i < months; i++) {
      payments->payment[i].percent = remains * rate_month;
      payments->payment[i].total = month_debt;
      payments->payment[i].debt = month_debt - payments->payment[i].percent;
      remains -= payments->payment[i].debt;
      payments->payment[i].remains = remains;
      payments->total_percent += payments->payment[i].percent;
    }
  }

  return payments;
}

s21_payments *s21_credit_diff(int sum, int months, int rate) {
  /*
    1. Ежемесячный платеж по основному долгу = сумма кредита / количество
    платежных периодов в течение всего срока кредита.

    300 000 рублей / 6 месяцев = 50 000 рублей.

    2. Ежемесячная сумма начисленных процентов по кредиту = остаток основного
    долга в текущем периоде * годовая процентная ставка * число дней в
    платежном периоде (от 28 до 31) / число дней в году (365 или 366).

    1-й месяц = 300 000 рублей*20%*31/365=5 095,89 рубля.
    2-й месяц = 250 000 рублей*20%*31/365=4 246,58 рубля.
    3-й месяц = 200 000 рублей*20%*30/365=3 287,67 рубля.
    4-й месяц = 150 000 рублей*20%*31/365=2547,95 рубля.
    5-й месяц = 100 000 рублей*20%*30/365=1643,84 рубля.
    6-й месяц = 50 000 рублей*20%*31/365=849,32 рубля.

    3. Ежемесячный платеж по кредиту = ежемесячный платеж по основному долгу +
    ежемесячная сумма начисленных процентов по кредиту.

    1-й месяц = 50 000 рублей+5 095,89 рубля=55 095,89 рубля.
    2-й месяц = 50 000 рублей+4 246,58 рубля=54 246,58 рубля.
    3-й месяц = 50 000 рублей+3 287,67 рубля=53 287,67 рубля.
    4-й месяц = 50 000 рублей+2 547,95 рубля=52 547,95 рубля.
    5-й месяц = 50 000 рублей+1 643,84 рубля=51 643,84 рубля.
    6-й месяц = 50 000 рублей+849,32 рубля=50 849,32 рубля.

    Итого платежи по кредиту составили 317 671,25 рубля.
   */
  args args = {0};

  s21_payments *payments = (s21_payments *)malloc(sizeof(s21_payments));
  if (payments) {
    payments->total_percent = 0;
    payments->payment = (s21_payment *)malloc(months * sizeof(s21_payment));
    if (payments->payment) {
      payments->count = months;
    } else {
      free(payments);
      payments = NULL;
    }
  }

  if (payments) {
    int curr_day;
    int curr_month;
    int curr_year;
    if (get_current_date(&curr_day, &curr_month, &curr_year)) {
      args.sum = sum;
      args.months = months;
      args.rate = rate;
      args.curr_day = curr_day;
      args.curr_month = curr_month;
      args.curr_year = curr_year;
      args.payments = payments;
    } else {
      free(payments->payment);
      free(payments);
      payments = NULL;
    }
  }

  if (payments) {
    calc_diff(&args);
  }

  return payments;
}

static void calc_diff(args *args) {
  int days_in_year = get_days_in_year(args->curr_year);
  double remains = args->sum;
  args->rate /= 100;

  double month_debt = args->sum / args->months;

  for (int i = 0; i < args->months; i++) {
    int days_in_month = get_days_in_month(args->curr_month, days_in_year);

    args->payments->payment[i].debt = month_debt;
    args->payments->payment[i].remains = remains - month_debt;
    args->payments->payment[i].percent =
        remains * args->rate * days_in_month / days_in_year;
    args->payments->payment[i].total =
        month_debt + args->payments->payment[i].percent;
    args->payments->total_percent += args->payments->payment[i].percent;

    remains = args->payments->payment[i].remains;

    args->curr_month++;

    if (args->curr_month > 12) {
      args->curr_month = 1;
      args->curr_year++;
      days_in_year = get_days_in_year(args->curr_year);
    }
  }
}

static int get_days_in_month(int month, int days_in_year) {
  int result;
  switch (month) {
    case 2:
      result = days_in_year == 365 ? 28 : 29;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      result = 30;
      break;
    default:
      result = 31;
  }
  return result;
}

static int get_days_in_year(int year) {
  int result = 0;
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
    result = 366;
  } else {
    result = 365;
  }
  return result;
}

static bool get_current_date(int *day, int *month, int *year) {
  bool result = true;
  time_t rawtime = time(NULL);
  struct tm *ptm = NULL;

  if (rawtime != -1) {
    ptm = localtime(&rawtime);
  } else {
    result = false;
  }

  if (ptm) {
    *day = ptm->tm_mday;
    *month = ptm->tm_mon + 1;
    *year = ptm->tm_year + 1900;
  } else {
    result = false;
  }

  return result;
}
