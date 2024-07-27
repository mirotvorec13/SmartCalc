#include "creditcalc.h"
#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreditCalc)
{
    ui->setupUi(this);
}

CreditCalc::~CreditCalc()
{
    delete ui;
}

void CreditCalc::on_Calculation_pressed()
{
    ui->calcTable->clear();

    s21_paymants *payments = NULL;
    if (ui->Different->isChecked()) {
        payments = s21_credit_diff(ui->SummCred->value(), ui->TermCred->value(), ui->BidCred->value());
    } else if (ui->Annuitet->isChecked()){
        payments = s21_credit_annuent(ui->SummCred->value(), ui->TermCred->value(), ui->BidCred->value());
    }

    if (payments) {
        ui->calcTable->clear();
        ui->calcTable->setColumnCount(4);
        ui->calcTable->setHorizontalHeaderLabels({"Платеж по %", "По долгу", "Сумма", "Остаток"});
        ui->calcTable->setRowCount(payments->count);

        for (int i = 0; i < payments->count; i++)
        {
            ui->calcTable->setItem(i, 0, new QTableWidgetItem(QString::number(payments->payment[i].percent, 'f', 2)));
            ui->calcTable->setItem(i, 1, new QTableWidgetItem(QString::number(payments->payment[i].debt, 'f', 2)));
            ui->calcTable->setItem(i, 2, new QTableWidgetItem(QString::number(payments->payment[i].total, 'f', 2)));
            ui->calcTable->setItem(i, 3, new QTableWidgetItem(QString::number(payments->payment[i].remains, 'f', 2)));
        }
        ui->ResCalcCred->setText(QString::number(payments->total_percent + ui->SummCred->value(), 'f', 2));
        ui->ResCalcPrec->setText(QString::number(payments->total_percent, 'f', 2));
        s21_payments_free(payments);
    } else {
        ui->calcTable->clear();
        ui->calcTable->setColumnCount(1);
        ui->calcTable->setRowCount(1);
        ui->calcTable->setItem(1, 0, new QTableWidgetItem("Error calculation!"));
    }
}



void CreditCalc::on_ResetButton_pressed()
{
    ui->calcTable->setColumnCount(0);
    ui->calcTable->setRowCount(0);
    ui->calcTable->clear();
}

