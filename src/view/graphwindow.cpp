#include "graphwindow.h"

#include <iostream>

#include "ui_graphwindow.h"

graphWindow::graphWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::graphWindow) {
  ui->setupUi(this);
  ui->widget->setBackground(QBrush(Qt::black));
  ui->widget->xAxis->setBasePen(QPen(Qt::white));
  ui->widget->yAxis->setBasePen(QPen(Qt::white));
  ui->widget->xAxis->setTickPen(QPen(Qt::white));
  ui->widget->yAxis->setTickPen(QPen(Qt::white));
  ui->widget->xAxis->setSubTickPen(QPen(Qt::white));
  ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
  ui->widget->xAxis->setTickLabelColor(Qt::white);
  ui->widget->yAxis->setTickLabelColor(Qt::white);
  ui->widget->xAxis->setLabelColor(Qt::white);
  ui->widget->yAxis->setLabelColor(Qt::white);
}

graphWindow::~graphWindow() { delete ui; }

void graphWindow::on_pushButton_back_clicked() {
  this->close();
  emit MainWindow();
}

void graphWindow::pasteEquation(QString plotLine) {
  ui->lineEdit_equation->setText(plotLine);

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->replot();
}

void graphWindow::on_pushButton_create_clicked() {
  double xMax = ui->lineEdit_right_xZone->text().toDouble();
  double xMin = ui->lineEdit_left_xZone->text().toDouble();
  double yMax = ui->lineEdit_right_yZone->text().toDouble();
  double yMin = ui->lineEdit_left_yZone->text().toDouble();

  if ((xMax >= 1000000) || (xMin <= -1000000) || (yMax >= 1000000) ||
      (yMin <= -1000000)) {
    QMessageBox::critical(this, "Error",
                          "The maximum display areas have been exceeded");
    return;
  }
  const int numPoints = 801;
  QVector<double> x(numPoints), y(numPoints);
  double step = (xMax - xMin) / numPoints;
  for (int i = 0; i < numPoints; ++i) {
    double xValue = xMin + i * step;
    x[i] = xValue;
    QString expression = ui->lineEdit_equation->text();
    expression.replace("x", QString::number(xValue, 'g', 7));
    QByteArray ba = expression.toLatin1();
    char *line = ba.data();

    try {
      double yValue = controller.CalculateExpression(line);
      if (yValue > 10 || yValue < -10) {
        yValue = qQNaN();
      }
      y[i] = yValue;
    } catch (const std::invalid_argument &e) {
      QMessageBox::critical(this, "Error",
                            QString("Build error: %1").arg(e.what()));
      return;
    } catch (const std::runtime_error &e) {
      y[i] = qQNaN();
    }
  }

  ui->widget->addGraph();
  QPen linePen(Qt::yellow);
  linePen.setWidth(2);
  ui->widget->graph(0)->setPen(linePen);
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);
  ui->widget->replot();
}
