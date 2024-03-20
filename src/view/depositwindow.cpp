#include "depositwindow.h"

#include "ui_depositwindow.h"

depositWindow::depositWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::depositWindow) {
  ui->setupUi(this);
  ui->lineEditcredit_sum_deposit->setFocus();
}

depositWindow::~depositWindow() { delete ui; }

void depositWindow::on_pushButton_back_clicked() {
  this->close();
  emit QMainWindow();
}

void depositWindow::on_pushButton_clear_clicked() {
  ui->lineEditcredit_sum_deposit->clear();
  ui->lineEdit_deposit_time->clear();
  ui->lineEdit_percent->clear();
  ui->lineEdit_percent_tax->clear();
  ui->lineEdit_total_summ->clear();
  ui->lineEdit_tax_withheld->clear();
  ui->lineEdit_total_with_tax->clear();
}

void depositWindow::on_pushButton_calk_res_clicked() {
  // summ - сумма вклада
  // n - срок размещения мес
  // interest_rate - Процентная ставка
  // tax_rate - налоговая ставка
  // periodicity_payments - периодичность выплат; 1 - месячная; 2 - в конце
  // capitalization - периодичность капитализации; 1 - месячная; 2 - в конце
  // count_add - пополнение раз в месяц ; 1 - месячная; 2 - отсутствуют
  // add - на какую сумму пополнения
  // count_sub - снятие раз в месяц; 1 - месячная; 2 - отсутствуют
  // sub - на какую сумму выплаты
  // result - сумма вклада с процентами
  // tax_with - удержано налогов
  // accrued_interest - начислено процентов

  int error = 0;
  double sum = ui->lineEditcredit_sum_deposit->text().toDouble();
  double credit_time = ui->lineEdit_deposit_time->text().toDouble();
  double interest_rate = ui->lineEdit_percent->text().toDouble();
  double tax_rate = ui->lineEdit_percent_tax->text().toDouble();
  int periodicity_payments = 0;
  int capitalization = 0;
  int count_add = 2;
  double add = ui->lineEdit_add_one_month->text().toDouble();
  int count_sub = 2;
  double sub = ui->lineEdit_leave_one_month->text().toDouble();

  if ((ui->checkBox_payment_in_end->isChecked() &&
       ui->checkBox_payment_in_month->isChecked()) ||
      (!ui->checkBox_payment_in_end->isChecked() &&
       !ui->checkBox_payment_in_month->isChecked())) {
    QMessageBox::critical(this, "Error", "Error");

    error = 1;
  } else if (ui->checkBox_payment_in_month->isChecked()) {
    periodicity_payments = 1;
  } else if (ui->checkBox_payment_in_end->isChecked()) {
    periodicity_payments = 2;
  }

  if (ui->checkBox_kap_1_month->isChecked()) {
    capitalization = 1;
  } else if (!ui->checkBox_kap_1_month->isChecked()) {
    capitalization = 2;
  }

  if (ui->checkBox_add_once_month->isChecked()) {
    count_add = 1;
    add = ui->lineEdit_add_one_month->text().toDouble();
  }

  if (ui->checkBox_sub_once_month->isChecked()) {
    count_sub = 1;
    sub = ui->lineEdit_leave_one_month->text().toDouble();
  }

  if (error == 0) {
    MyCalculator::Deposit::DepositOutput depositOutput;
    controller.CalculateDeposit(sum, credit_time, interest_rate, tax_rate,
                                periodicity_payments, capitalization, count_add,
                                add, count_sub, sub, depositOutput);

    QString total = QString::number(depositOutput.accrued_interest, 'f', 2);
    ui->lineEdit_total_summ->setText(total);

    QString with_tax = QString::number(depositOutput.result, 'f', 2);
    ui->lineEdit_total_with_tax->setText(with_tax);

    QString tax = QString::number(depositOutput.tax_with, 'f', 2);
    ui->lineEdit_tax_withheld->setText(tax);
  }
}
