#include "PlotView.h"
#include "ui_PlotView.h"
#include "mainwindow.h"

PlotView::PlotView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlotView)
{
    ui->setupUi(this);

}

PlotView::~PlotView() { delete ui; }
void PlotView::PlotGraph(std::pair<QVector<double>, QVector<double>> val, double max_x, double max_y) {


    // QPen pen;
    // pen.setColor(QColor(132,38, 87));
    ui->widget->xAxis->setRange(-max_x, max_x);
    ui->widget->yAxis->setRange(-max_y, max_y);
    ui->widget->addGraph();//->setPen(pen);
    if (ui->Dot->isChecked()) {
        ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle , 2));
    }
    ui->widget->graph(0)->addData(val.first, val.second);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setBackground(QColor(235, 234, 230));
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->replot();

}


void PlotView::on_Clear_graph_pressed()
{
    ui->widget->clearGraphs();
    ui->widget->replot();
}


void PlotView::on_Clear_graph_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->replot();
}

