#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "../../gui/cli/main.h"
#define WIDTH_MAIN 10
#define HEIGHT_MAIN 20
#define COUNT_FIGURES 7
#define VALUE_SAMPLE 5

typedef struct figure
{
  int x;
  int y;
  int **blocks;
} figure;
#ifdef __cplusplus
extern "C"
{
#endif
  void userInput(UserAction_t action, bool hold);
  void main_game();
  int window_of_game(int period, int new_game);
  GameInfo_t updateCurrentState();
  GameInfo_t get_info_extern();
  void main_menu();
  int init_object(GameInfo_t *var, FILE *file);
  int memory_allocation_field(GameInfo_t *var);
  void free_field(GameInfo_t *var);
  void free_next(GameInfo_t *var);
  int read_high_score(int *high_score, FILE *file);
  int init_ints(GameInfo_t *var);
  int init_next_figure(GameInfo_t *var);
  int memory_allocation_next(GameInfo_t *var);
  int init_current_figure(figure *current, int **ptr_next);
  GameInfo_t static_storage(int new_current, int new_game, UserAction_t action);
  int move_down(figure *var);
  int collision(GameInfo_t var, figure current);
  int move_up(figure *var);
  int put_current(GameInfo_t *var, figure current);
  int count_points(GameInfo_t *var);
  int move_upper_lines(int i, GameInfo_t *var);
  int update_score(GameInfo_t *var);
  int create_new_figure(GameInfo_t *var, figure *current);
  int filled_line(int i, GameInfo_t *var);
  void free_figure(figure *var);
  int memory_allocation_figure(figure *var);
  int erase_field(GameInfo_t *var, figure current);
  void moving_figure(WINDOW *var_window_of_game);
  void processing_down(GameInfo_t *var, figure *current, int *lvl, int check_high_score);
  int move_right(figure *var);
  int move_left(figure *var);
  void output_pause_window();
  void free_in_the_end_of_game(GameInfo_t *var, figure *current);
  int rotate_figure(GameInfo_t *var, figure *current);
  void output_additional_window(WINDOW *win, GameInfo_t *var);
  int get_start_for_add(GameInfo_t *var);
  void output_next_figure(WINDOW *win, GameInfo_t *var);
  int clear_field(GameInfo_t *var);
  int writening_high_score(int score);
  int square(figure *figure);
  void init_field(GameInfo_t *var, int number);
  GameInfo_t do_action(GameInfo_t *var, figure *current, UserAction_t action,
                       int check_high_score, int *lvl);
  void output_control_window(int start_x, int start_y);
  void output_end_of_game_window();
  void output_win();
#ifdef __cplusplus
}
#endif