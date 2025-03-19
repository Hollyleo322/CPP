#include <QApplication>
#include <QtWidgets>
#include <iostream>

#include "../../../brick_game/tetris/s21_tetris.h"
#include "mainwindows21snake.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#ifdef snake
  s21::Snake *snake_1 = s21::get_snake();
  snake_1->set_field(snake_1->get_body());
  s21::MainWindowS21Snake b(snake_1->get_info(), snake_1);
  b.show();
#else
  GameInfo_t info = static_storage(1, 1, Up);
  s21::MainWindowS21Snake b(&info, nullptr);
  b.show();
#endif
  return a.exec();
}
