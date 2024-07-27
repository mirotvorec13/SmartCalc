#pragma once

#include <QDialog>

#include "PlotLibrary/qcustomplot.h"

namespace Ui {
class PlotView;
}

class PlotView : public QDialog {
  Q_OBJECT

 public:
  explicit PlotView(QWidget *parent = nullptr);

  // void setText(const QString &newText) {
  //     text = newText;
  // }

  void PlotGraph(std::pair<QVector<double>, QVector<double>> val, double max_x,
                 double max_y);
  ~PlotView();
  void on_Clear_graph_pressed();

 private slots:
  void on_Clear_graph_clicked();

 private:
  Ui::PlotView *ui;
  QString text;
};
