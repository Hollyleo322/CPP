#include "mainwindows21snake.h"
using namespace s21;
MainWindowS21Snake::MainWindowS21Snake(GameInfo_t *ptr_obj, Snake *ptr_snake,
                                       QWidget *parent)
    : QWidget(parent),
      ptr_game_info(ptr_obj),
      start_game(new QPushButton("Start game", this)),
      input_settings(new QPushButton("Input settings", this)),
      exit(new QPushButton("exit", this)),
      ptr_game(new game_window(ptr_snake, ptr_obj, this)),
      layout(new QVBoxLayout) {
#ifndef snake
  this->setWindowIcon(
      QIcon("gui/desktop/s21_snake/resourses/icons/tetris.png"));
#else
  this->setWindowIcon(QIcon("gui/desktop/s21_snake/resourses/icons/snake.png"));
#endif
  set_logo(layout);
  set_qlabel(layout);
  set_palette();
  setFixedSize(800, 800);
  layout->addStretch(1);  // Направляем кнопки вниз
  set_buttons(layout);
  setLayout(layout);
  MainWindowS21Snake::set_in_middle_widgets(
      this);  // Перемещаем окно в центр экрана
}
void MainWindowS21Snake::set_logo(QVBoxLayout *layout) {
  QLabel *logo = new QLabel(this);
  QPixmap pix("gui/desktop/s21_snake/resourses/logo.png");
  logo->setPixmap(pix);
  logo->setScaledContents(true);
  layout->addWidget(logo, 0, Qt::AlignLeft);
}
void MainWindowS21Snake::start_game_window() {
  this->close();
  ptr_game->setFixedSize(800, 800);
  ptr_game->start_timer();
  MainWindowS21Snake::set_in_middle_widgets(
      ptr_game);  // Перемещаем  игровое окно в центр экрана
  ptr_game->show();
}
void MainWindowS21Snake::set_qlabel(QVBoxLayout *layout) {
#ifdef snake
  QLabel *lable = new QLabel("s21 Snake", this);
  lable->setStyleSheet("color: green;");
#else
  QLabel *lable = new QLabel("s21 Tetris", this);
  lable->setStyleSheet("color: Blue;");
#endif
  QFont snakeFont("Times", 64, QFont::Bold);
  lable->setFont(snakeFont);
  layout->addWidget(lable, 0, Qt::AlignCenter);
}
void MainWindowS21Snake::set_palette() {
  QPalette palette;
  palette.setColor(QPalette::Window, Qt::black);  // Цвет фона окна
  palette.setColor(QPalette::WindowText, Qt::black);  // Цвет текста в окне
  palette.setColor(QPalette::Button, Qt::white);  // Цвет кнопки
  palette.setColor(QPalette::ButtonText, Qt::black);  // Цвет текста на кнопке
  palette.setColor(QPalette::Highlight, Qt::white);  // Цвет выделения
  palette.setColor(QPalette::HighlightedText,
                   Qt::white);  // Цвет текста при выделении
  this->setPalette(palette);
}
void MainWindowS21Snake::set_buttons(QVBoxLayout *layout) {
  QFont serifFont("Times", 15, QFont::Bold);
  exit->setFixedWidth(400);
  start_game->setFixedWidth(400);
  input_settings->setFixedWidth(400);
#ifdef snake
  QIcon snk_i("gui/desktop/s21_snake/resourses/icons/snake.png");
#else
  QIcon snk_i("gui/desktop/s21_snake/resourses/icons/tetris.png");
#endif
  QIcon cookie("gui/desktop/s21_snake/resourses/icons/2.png");
  exit->setIcon(cookie);
  start_game->setIcon(snk_i);
  exit->setFont(serifFont);
  start_game->setFont(serifFont);
  input_settings->setFont(serifFont);
  connect(start_game, SIGNAL(clicked()), this, SLOT(start_game_window()));
  connect(input_settings, SIGNAL(clicked()), this, SLOT(output_settings()));
  connect(exit, SIGNAL(clicked(bool)), QApplication::instance(), SLOT(quit()));
  layout->addWidget(start_game, 0, Qt::AlignCenter);
  layout->addWidget(input_settings, 0, Qt::AlignCenter);
  layout->addWidget(exit, 0, Qt::AlignCenter);
}
void MainWindowS21Snake::output_settings() {
  QMessageBox *settings = new QMessageBox(this);
  settings->setWindowTitle("Settings");
  settings->setText(
      tr("s - restart\n"
         "SPACE - Action\n"
         "q - exit from game\n"
         "ENTER - pause\n"
         "< > v ^ arrows key - move\n"));
  settings->exec();
  settings->close();
}