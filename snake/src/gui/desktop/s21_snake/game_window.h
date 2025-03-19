#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <QtWidgets>
#include <QDialog>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include "../../../brick_game/snake/snake.h"
#include "../../../brick_game/tetris/s21_tetris.h"
#include <QPainter>
namespace s21
{
    class game_window : public QWidget
    {
        Q_OBJECT
    private:
        Snake *ptr_snake;
        GameInfo_t *ptr_info;
        QTimer *timer;

    public:
        game_window(Snake *snake_t, GameInfo_t *ptr_obj, QWidget *parent = nullptr) : ptr_snake(snake_t), ptr_info(ptr_obj)
        {
            timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &game_window::update_screen);
#ifndef snake
            this->setWindowIcon(QIcon("gui/desktop/s21_snake/resourses/icons/tetris.png"));
#else
            this->setWindowIcon(QIcon("gui/desktop/s21_snake/resourses/icons/snake.png"));
#endif
            set_palette();
        }
        void output_game_over();
        void output_pause();
        void paint_added_info(QPainter *painter);
        void start_timer() { timer->start(1000); }
        void set_palette();
        void output_win();

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void paintEvent(QPaintEvent *event) override;
    private slots:
        void update_screen();
    };
}
#endif // GAME_WINDOW_H
