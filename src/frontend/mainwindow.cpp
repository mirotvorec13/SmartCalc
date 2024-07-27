#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "validator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->Button_0, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_1, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_2, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_3, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_4, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_5, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_6, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_7, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_8, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_9, SIGNAL(released()), this, SLOT(buttons_pressed()));

  connect(ui->Button_dot, SIGNAL(released()), this, SLOT(buttons_pressed()));

  connect(ui->open_bracket, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->close_bracket, SIGNAL(released()), this, SLOT(buttons_pressed()));

  connect(ui->Button_mod, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_div, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_mul, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_sub, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_sum, SIGNAL(released()), this, SLOT(buttons_pressed()));

  connect(ui->Button_cos_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_sin_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_tan_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_acos_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_asin_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_atan_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_sqrt_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_ln_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_log_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_pow, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_x, SIGNAL(released()), this, SLOT(buttons_pressed()));
  connect(ui->Button_AC, SIGNAL(released()), this,
          SLOT(on_Button_AC_pressed()));
  connect(ui->Button_Backspace, SIGNAL(released()), this,
          SLOT(buttons_pressed()));
  connect(ui->Button_enter, SIGNAL(released()), this,
          SLOT(on_Button_enter_pressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Button_AC_pressed() {
  _PrintStr.clear();
  ui->InputStr->clear();
  ui->OutputStr->clear();
  ui->checkBox->setChecked(false);
  plotView.on_Clear_graph_pressed();
}

void MainWindow::on_Button_enter_pressed() {
  if (_PrintStr == "") {
    return;
  }

  s21_calc_result calc_result;

  bool err = false;

  if (!validator(&_PrintStr)) {
    err = true;
  }

  if (!err) {
    QByteArray str_bit = _PrintStr.toLocal8Bit();
    ui->OutputStr->setText(_PrintStr);
    char *result_str = (char *)str_bit.constData();
    if (ui->checkBox->isChecked()) {
      calc_result = s21_calc_x(result_str, ui->double_x_value->value());
    } else {
      calc_result = s21_calc(result_str);
    }

    if (!calc_result.error) {
      QString res_str = QString::number(calc_result.result, 'g', 7);
      ui->OutputStr->setText(res_str);
    } else {
      err = true;
    }
  }

  if (err) {
    ui->OutputStr->setText("CalculationError!");
  }

  ui->checkBox->setChecked(false);
  ui->InputStr->clear();
  _PrintStr.clear();
}

void MainWindow::buttons_pressed() {
  QPushButton *button = (QPushButton *)sender();

  if (button->text() == "x") {
    ui->checkBox->setChecked(true);
  }

  if (button->text() != "<-") {
    _PrintStr.push_back(button->text());
    if (button->text() == "cos" || button->text() == "sin" ||
        button->text() == "tan" || button->text() == "acos" ||
        button->text() == "asin" || button->text() == "atan" ||
        button->text() == "sqrt" || button->text() == "ln" ||
        button->text() == "log") {
      _PrintStr.push_back("(");
    }
  }
  ui->InputStr->setText(_PrintStr);
}

void MainWindow::on_Button_build_graph_pressed() {
  plotView.on_Clear_graph_pressed();
  bool err = false;

  int points_cnt =
      (ui->Range->value() * 2 / ui->Step_for_graph->value());
  if (points_cnt > 2000000) {
    err = true;
  }

  if (err || !validator(&_PrintStr)) {
    err = true;
  }
  int range = ui->Range->value();
  if (!err) {
    QByteArray str_bit = _PrintStr.toLocal8Bit();
    char *result = (char *)str_bit.constData();
    s21_calc_range_result calc_result =
        s21_calc_range(result, -range, range, ui->Step_for_graph->value());

    if (!calc_result.error) {
      // Генерация x и y
      QVector<double> xValues;
      QVector<double> yValues;

      for (int i = 0; i < calc_result.coords.count; ++i) {
        xValues.append(calc_result.coords.x[i]);
        yValues.append(calc_result.coords.y[i]);
      }

      plotView.PlotGraph(std::make_pair(xValues, yValues), ui->X_MAX->value(),
                         ui->Y_MAX->value());
      plotView.show();

      ui->InputStr->setText("");
      _PrintStr.clear();
    } else {
      err = true;
    }
  }

  if (err == true) {
    ui->OutputStr->setText("CalculationError!");
    return;
  } else {
    ui->OutputStr->setText("");
  }

  // Вызов функции PlotGraph для построения графика
}

void MainWindow::on_checkBox_stateChanged(int arg1) {}

void MainWindow::on_Button_Backspace_pressed() { _PrintStr.chop(1); }

void MainWindow::on_pushButton_4_pressed()
{
    creditCalc.show();
     // credit_diff(2000000, 60, 20);
    // s21_calc("2+2");
}

