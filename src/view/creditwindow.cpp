#include "creditwindow.h"

#include "ui_creditwindow.h"

creditWindow::creditWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::creditWindow) {
  ui->setupUi(this);
  ui->lineEditcredit_sum->setFocus();
}

creditWindow::~creditWindow() { delete ui; }

void creditWindow::on_pushButton_back_clicked() {
  this->close();
  emit QMainWindow();
}

void creditWindow::on_pushButton_clear_clicked() {
  ui->lineEditcredit_sum->clear();
  ui->lineEdit_credit_time->clear();
  ui->lineEdit_percent->clear();
  ui->lineEdit_first_paymen->clear();
  ui->lineEdit_last_payment->clear();
  ui->lineEdit_overpayment->clear();
  ui->lineEdit_total_payment->clear();
}

void creditWindow::on_pushButton_calk_res_clicked() {
  double credit_sum = ui->lineEditcredit_sum->text().toDouble();
  double credit_time = ui->lineEdit_credit_time->text().toDouble();
  double percent = ui->lineEdit_percent->text().toDouble();
  int type_payment = 2;
  int error = 0;

  if ((ui->checkBox_AN->isChecked() && ui->checkBox_DIF->isChecked()) ||
      (!ui->checkBox_AN->isChecked() && !ui->checkBox_DIF->isChecked())) {
    QMessageBox::critical(
        this, "Error", "Choose one payment option: Annuity or Differentiated");
    error = 1;

  } else if (ui->checkBox_AN->isChecked()) {
    type_payment = 0;
  } else if (ui->checkBox_DIF->isChecked()) {
    type_payment = 1;
  }
  if (error == 0) {
    MyCalculator::Credit::PaymentOutput paymentOutput;
    controller.CalculateCredit(credit_sum, credit_time, percent, type_payment,
                               paymentOutput);

    QString first = QString::number(paymentOutput.first_payment, 'f', 2);
    ui->lineEdit_first_paymen->setText(first);

    QString last = QString::number(paymentOutput.last_payment, 'f', 2);
    ui->lineEdit_last_payment->setText(last);

    QString total = QString::number(paymentOutput.total_payment, 'f', 2);
    ui->lineEdit_total_payment->setText(total);

    QString over = QString::number(paymentOutput.overpayment, 'f', 2);
    ui->lineEdit_overpayment->setText(over);
  } else {
    ui->lineEdit_first_paymen->clear();
    ui->lineEdit_last_payment->clear();
    ui->lineEdit_overpayment->clear();
    ui->lineEdit_total_payment->clear();
  }
}
