#ifndef CREDITWINDOW_H_
#define CREDITWINDOW_H_

#include <QMainWindow>
#include <QMessageBox>

#include "../controller/controller.h"

namespace Ui {
class creditWindow;
}

class creditWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit creditWindow(QWidget *parent = nullptr);
  ~creditWindow();

 private slots:
  void on_pushButton_back_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_calk_res_clicked();

 private:
  Ui::creditWindow *ui;
  MyCalculator::CalcController controller;
};

#endif  // CREDITWINDOW_H_
