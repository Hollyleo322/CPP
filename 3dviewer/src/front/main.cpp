#include <QApplication>
#include <iostream>

#include "../back/parser.h"
#include "../back/scene.h"
#include "../back/transform.h"
#include "mainwindow.h"
using namespace s21;
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  Control ctr(&facade);
  MainWindow MainWindow(&ctr);
  MainWindow.show();
  return a.exec();
}
