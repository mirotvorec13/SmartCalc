#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDialog>

extern "C" {
#include "../backend/s21_calc.h"
}

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_Calculation_pressed();

  void on_ResetButton_pressed();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
