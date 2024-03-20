#ifndef DEPOSITWINDOW_H_
#define DEPOSITWINDOW_H_

#include <QButtonGroup>
#include <QMainWindow>
#include <QMessageBox>

#include "../controller/controller.h"

namespace Ui {
class depositWindow;
}

class depositWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit depositWindow(QWidget *parent = nullptr);
  ~depositWindow();

 private slots:
  void on_pushButton_back_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_calk_res_clicked();

 private:
  Ui::depositWindow *ui;
  MyCalculator::CalcController controller;
};

#endif  // DEPOSITWINDOW_H_
