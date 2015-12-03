#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CPU.h"
#include <vector>
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QString>
#include <QFileDialog>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  CPU CP;
  std::vector< std::pair<QLabel*, int> > Labels;
  int used[10];
  int numOfLabelsToUpdate;
  int count[10];
  QString filename = "";

private slots:
  void on_NextCycle_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
