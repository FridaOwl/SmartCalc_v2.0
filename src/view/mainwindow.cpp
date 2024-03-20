#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->lineEdit_equation->setFocus();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_1_clicked() {
  ui->lineEdit_equation->insert("1");
}

void MainWindow::on_pushButton_2_clicked() {
  ui->lineEdit_equation->insert("2");
}

void MainWindow::on_pushButton_3_clicked() {
  ui->lineEdit_equation->insert("3");
}

void MainWindow::on_pushButton_4_clicked() {
  ui->lineEdit_equation->insert("4");
}

void MainWindow::on_pushButton_5_clicked() {
  ui->lineEdit_equation->insert("5");
}

void MainWindow::on_pushButton_6_clicked() {
  ui->lineEdit_equation->insert("6");
}

void MainWindow::on_pushButton_7_clicked() {
  ui->lineEdit_equation->insert("7");
}

void MainWindow::on_pushButton_8_clicked() {
  ui->lineEdit_equation->insert("8");
}

void MainWindow::on_pushButton_9_clicked() {
  ui->lineEdit_equation->insert("9");
}

void MainWindow::on_pushButton_0_clicked() {
  ui->lineEdit_equation->insert("0");
}

void MainWindow::on_pushButton_tochka_clicked() {
  ui->lineEdit_equation->insert(".");
}

void MainWindow::on_pushButton_plus_clicked() {
  ui->lineEdit_equation->insert("+");
}

void MainWindow::on_pushButton_minus_clicked() {
  ui->lineEdit_equation->insert("-");
}

void MainWindow::on_pushButton_multiply_clicked() {
  ui->lineEdit_equation->insert("*");
}

void MainWindow::on_pushButton_divide_clicked() {
  ui->lineEdit_equation->insert("/");
}

void MainWindow::on_pushButton_uo_minus_clicked() {
  ui->lineEdit_equation->insert("-");
}

void MainWindow::on_pushButton_mod_clicked() {
  ui->lineEdit_equation->insert("%");
}

void MainWindow::on_pushButton_close_bracket_clicked() {
  ui->lineEdit_equation->insert(")");
}

void MainWindow::on_pushButton_open_bracket_clicked() {
  ui->lineEdit_equation->insert("(");
}

void MainWindow::on_pushButton_pow_clicked() {
  ui->lineEdit_equation->insert("^");
}

void MainWindow::on_pushButton_tan_clicked() {
  ui->lineEdit_equation->insert("tan(");
}

void MainWindow::on_pushButton_cos_clicked() {
  ui->lineEdit_equation->insert("cos(");
}

void MainWindow::on_pushButton_sin_clicked() {
  ui->lineEdit_equation->insert("sin(");
}

void MainWindow::on_pushButton_atan_clicked() {
  ui->lineEdit_equation->insert("atan(");
}

void MainWindow::on_pushButton_acos_clicked() {
  ui->lineEdit_equation->insert("acos(");
}

void MainWindow::on_pushButton_asin_clicked() {
  ui->lineEdit_equation->insert("asin(");
}

void MainWindow::on_pushButton_log_clicked() {
  ui->lineEdit_equation->insert("log(");
}

void MainWindow::on_pushButton_ln_clicked() {
  ui->lineEdit_equation->insert("ln(");
}

void MainWindow::on_pushButton_sqrt_clicked() {
  ui->lineEdit_equation->insert("sqrt(");
}

void MainWindow::on_pushButton_x_clicked() {
  ui->lineEdit_equation->insert("x");
}

void MainWindow::on_pushButton_ac_clicked() {
  ui->lineEdit_equation->clear();
  ui->lineEdit_x_param->clear();
}

void MainWindow::on_pushButton_equal_clicked() {
  QString expression = ui->lineEdit_equation->text();
  expression.replace("x", ui->lineEdit_x_param->text());

  try {
    std::string expressionStd = expression.toStdString();
    double result = controller.CalculateExpression(expressionStd);
    ui->lineEdit_equation->clear();
    ui->lineEdit_equation->insert(QString::number(result));
  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", QString("Error: %1").arg(e.what()));
  }
}

void MainWindow::on_pushButton_FUNCT_clicked() {
  graphWindow* graph = new graphWindow();

  connect(this, &MainWindow::signal_to_pasteEquation, graph,
          &graphWindow::pasteEquation);
  QString str2 = ui->lineEdit_equation->text();

  bool isNumeric = false;
  str2.toDouble(&isNumeric);

  if (!str2.isEmpty() && isNumeric) {
    QMessageBox::critical(this, "Error",
                          "There's only a number in the equation! Use "
                          "trigonometric functions to plot the graph");
  } else {
    graph->show();
  }
  emit signal_to_pasteEquation(str2);
}

void MainWindow::on_pushButton_CREDIT_clicked() {
  creditWindow* credit = new creditWindow();
  credit->show();
}

void MainWindow::on_pushButton_DEPOSIT_clicked() {
  depositWindow* deposit = new depositWindow();
  deposit->show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    on_pushButton_equal_clicked();
  }

  QMainWindow::keyPressEvent(event);
}
