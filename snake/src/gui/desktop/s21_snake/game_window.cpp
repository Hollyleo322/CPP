#include "game_window.h"
using namespace s21;
void game_window::paintEvent(QPaintEvent *event) {
  *ptr_info = get_info_extern();
  if (ptr_info->pause == Win) {
    output_win();
  }
  if (ptr_info->speed == 0) {
    ptr_info->speed = 1;
  }
  timer->setInterval(1000 / ptr_info->speed);
  if (ptr_info->pause == Pause) {
    output_pause();
  }
  QPainter painter(this);
  painter.translate(width() / 10, height() / 10);
  painter.setBrush(QBrush(Qt::white));
  painter.setPen(Qt::black);
  for (int row = 0; row < 20; ++row) {
    for (int col = 0; col < 10; ++col) {
      if (ptr_info->field[row][col] == 1) {
        painter.save();
#ifdef snake
        painter.setBrush(QBrush(Qt::green));
#else
        painter.setBrush(QBrush(Qt::blue));
#endif
      }
      QRect cellRect(col * 30, row * 30, 30, 30);
      painter.drawRect(cellRect);
      if (ptr_info->field[row][col] == 1) {
        painter.restore();
      }
    }
  }
#ifdef snake
  painter.save();
  painter.setBrush(QBrush(Qt::red));
  QRect applerect((this->ptr_snake->get_apple() % 10) * 30,
                  (this->ptr_snake->get_apple() / 10) * 30, 30, 30);
  painter.drawRect(applerect);
  painter.restore();
#endif
  paint_added_info(&painter);
  if (ptr_info->pause == Pre_exit_situation) {
    output_game_over();
  }
}
void game_window::paint_added_info(QPainter *painter) {
  painter->save();
  QFont font("Times", 20, QFont::Bold);
  painter->setBrush(QBrush(Qt::black));
  painter->setPen(Qt::white);
  painter->setFont(font);
  painter->translate(400, 0);
#ifdef snake
  QPixmap snake_img("gui/desktop/s21_snake/resourses/snake.png");
  painter->drawPixmap(50, 0, snake_img);
#else
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (ptr_info->next[i][j] == 1) {
        painter->save();
        painter->setBrush(QBrush(Qt::white));
        painter->setPen(Qt::black);
        painter->drawRect(QRect((j) * 30, (i - 1) * 30, 30, 30));
        painter->restore();
      }
    }
  }
#endif
  QRect score_rect(0, 90, 170, 70);
  QRect speed_rect(0, 180, 170, 70);
  QRect level_rect(0, 270, 170, 70);
  QRect high_score_rect(0, 360, 170, 70);
  painter->drawRect(score_rect);
  painter->drawText(score_rect, Qt::AlignTop | Qt::AlignHCenter, "Score");
  painter->drawText(score_rect, Qt::AlignBottom | Qt::AlignHCenter,
                    QString::number(ptr_info->score));
  painter->drawRect(speed_rect);
  painter->drawText(speed_rect, Qt::AlignTop | Qt::AlignHCenter, "Speed");
  painter->drawText(speed_rect, Qt::AlignBottom | Qt::AlignHCenter,
                    QString::number(ptr_info->speed));
  painter->drawRect(level_rect);
  painter->drawText(level_rect, Qt::AlignTop | Qt::AlignHCenter, "Level");
  painter->drawText(level_rect, Qt::AlignBottom | Qt::AlignHCenter,
                    QString::number(ptr_info->level));
  painter->drawRect(high_score_rect);
  painter->drawText(high_score_rect, Qt::AlignTop | Qt::AlignHCenter,
                    "High score");
  painter->drawText(high_score_rect, Qt::AlignBottom | Qt::AlignHCenter,
                    QString::number(ptr_info->high_score));
  painter->restore();
}
void game_window::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Right:
      userInput(Right, false);
      break;
    case Qt::Key_Left:
      userInput(Left, false);
      break;
    case Qt::Key_Down:
      userInput(Down, true);
      break;
    case Qt::Key_Return:
      userInput(Pause, false);
      break;
    case Qt::Key_Space:
      userInput(Action, true);
      break;
    case Qt::Key_S:
      userInput(Start, false);
      break;
    case Qt::Key_Q:
      userInput(Terminate, false);
      auto quit = QApplication::instance();
      quit->quit();
      break;
  }
  this->update();
}
void game_window::update_screen() {
  *ptr_info = updateCurrentState();
  this->update();
}
void game_window::output_game_over() {
  timer->stop();
  QMessageBox *end = new QMessageBox(this);
  QMessageBox::StandardButtons std_pb = {QMessageBox::Reset,
                                         QMessageBox::Close};
  end->setStandardButtons(std_pb);
  end->setText("Game Over");
  int answer = end->exec();
  switch (answer) {
    case QMessageBox::Reset:
      userInput(Start, false);
      timer->start(1000);
      break;
    case QMessageBox::Close:
      userInput(Terminate, false);
      auto quit = QApplication::instance();
      quit->quit();
      break;
  }
}
void game_window::output_pause() {
  timer->stop();
  QMessageBox *pause = new QMessageBox(this);
  pause->setText("Pause");
  pause->exec();
  timer->start(1000);
  userInput(Pause, false);
}
void game_window::set_palette() {
  QPalette palette;
  palette.setColor(QPalette::Window, Qt::black);  // Цвет фона окна
  this->setPalette(palette);
}
void game_window::output_win() {
  timer->stop();
  QMessageBox *win = new QMessageBox(this);
  QMessageBox::StandardButtons std_pb = {QMessageBox::Reset,
                                         QMessageBox::Close};
  win->setStandardButtons(std_pb);
  win->setText("You win!");
  int answer = win->exec();
  switch (answer) {
    case QMessageBox::Reset:
      userInput(Start, false);
      timer->start(1000);
      break;
    case QMessageBox::Close:
      userInput(Terminate, false);
      auto quit = QApplication::instance();
      quit->quit();
      break;
  }
}