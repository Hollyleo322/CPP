#pragma once

#include <QColorDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "viewport.h"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE
namespace s21 {
class Viewport;
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Control *ctr, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Viewport *glWidget;
  Control *ptrControl;
  void toZeroSliders();
  void connectSlidersandSpinBoxes();
  void connectButtons();
 private slots:
  void showFileDialog();
  void showChangeColorPoints();
  void showColorDialog();
  void showChangeBackground();
};
}  // namespace s21