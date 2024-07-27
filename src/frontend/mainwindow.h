#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <QString>
#include <QVector>

#include "PlotView.h"
#include "creditcalc.h"

extern "C" {
#include "../backend/s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  // QString getText() const {
  //     return _PrintStr;
  // }

  ~MainWindow();

 private:
  QString _PrintStr;
  Ui::MainWindow *ui;
  QString _OutputStr;
  PlotView plotView;
  CreditCalc creditCalc;

 private slots:
  void buttons_pressed();
  void on_Button_build_graph_pressed();
  void on_Button_enter_pressed();
  void on_Button_AC_pressed();
  void on_checkBox_stateChanged(int arg1);
  void on_Button_Backspace_pressed();
  void on_pushButton_4_pressed();
};
#endif  // MAINWINDOW_H
