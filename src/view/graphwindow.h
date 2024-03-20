#ifndef GRAPHWINDOW_H_
#define GRAPHWINDOW_H_

#include <QMainWindow>
#include <QVector>

#include "../controller/controller.h"

namespace Ui {
class graphWindow;
}

class graphWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit graphWindow(QWidget *parent = nullptr);
  ~graphWindow();
 signals:
  void MainWindow();

 private slots:
  void on_pushButton_back_clicked();

  void on_pushButton_create_clicked();

 public slots:
  void pasteEquation(QString plotLine);

 private:
  Ui::graphWindow *ui;
  MyCalculator::CalcController controller;
};

#endif  // GRAPHWINDOW_H_
