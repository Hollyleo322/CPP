#include "s21_tetris.h"
int init_object(GameInfo_t *var, FILE *file) {
  int res = 0;
  if (!var || !file) {
    res = 1;
  } else {
    res |= (memory_allocation_field(var) << 1);
    res |= (read_high_score(&var->high_score, file) << 2);
    init_ints(var);
    res |= (memory_allocation_next(var) << 3);
    res |= (init_next_figure(var) << 4);
  }
  return res;
}
int memory_allocation_field(GameInfo_t *var) {
  int res = 0;
  if (!var) {
    res = 1;
  } else {
    var->field = malloc(sizeof(int *) * HEIGHT_MAIN);
    for (int i = 0; i < HEIGHT_MAIN; i++) {
      var->field[i] = calloc(WIDTH_MAIN, sizeof(int));
      if (!var->field[i]) {
        res = 1;
        break;
      }
    }
  }
  return res;
}
void free_field(GameInfo_t *var) {
  if (var->field) {
    for (int i = 0; i < HEIGHT_MAIN; i++) {
      free(var->field[i]);
    }
    free(var->field);
  }
}
void free_next(GameInfo_t *var) {
  if (var->next) {
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      free(var->next[i]);
    }
    free(var->next);
  }
}
int read_high_score(int *high_score, FILE *file) {
  int res = 0;
  if (!file || !high_score) {
    res = 1;
  } else {
    fscanf(file, "%d", high_score);
  }
  return res;
}
int init_ints(GameInfo_t *var) {
  int res = 0;
  if (var) {
    var->score = 0;
    var->level = 1;
    var->speed = 1;
    var->pause = 0;
  } else {
    res = 1;
  }
  return res;
}
int init_next_figure(GameInfo_t *var) {
  int res = 0;
  if (var) {
    int samples[][VALUE_SAMPLE][VALUE_SAMPLE] = {
        {{0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0},
         {0, 1, 1, 1, 1},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0},
         {0, 1, 0, 0, 0},
         {0, 1, 1, 1, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0},
         {0, 1, 1, 1, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0},
         {0, 0, 1, 1, 0},
         {0, 0, 1, 1, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0},
         {0, 0, 1, 1, 0},
         {0, 1, 1, 0, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0},
         {0, 1, 1, 1, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0},
         {0, 1, 1, 0, 0},
         {0, 0, 1, 1, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0}},
    };
    srand(time(NULL));
    int random = rand() % COUNT_FIGURES;
    if (!res) {
      for (int i = 0; i < VALUE_SAMPLE; i++) {
        for (int j = 0; j < VALUE_SAMPLE; j++) {
          var->next[i][j] = samples[random][i][j];
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}
int memory_allocation_next(GameInfo_t *var) {
  int res = 0;
  if (!var) {
    res = 1;
  } else {
    var->next = malloc(sizeof(int *) * VALUE_SAMPLE);
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      var->next[i] = calloc(VALUE_SAMPLE, sizeof(int));
      if (var->next[i] == NULL) {
        res = 1;
        break;
      }
    }
  }
  return res;
}
int init_current_figure(figure *current, int **ptr_next) {
  int res = 0;
  if (!current || !ptr_next) {
    res = 1;
  }
  if (!res) {
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      for (int j = 0; j < VALUE_SAMPLE; j++) {
        current->blocks[i][j] = ptr_next[i][j];
      }
    }
    current->x = WIDTH_MAIN / 2 - 3;
    current->y = 0;
  }
  return res;
}
GameInfo_t updateCurrentState() {
  GameInfo_t res = static_storage(0, 0, Down);
  return res;
}
GameInfo_t static_storage(int new_current, int new_game, UserAction_t action) {
  static GameInfo_t var;
  if (var.pause ==
      Change_level)  // if changed level, should to zero pause's variable
  {
    var.pause = Game;
  }
  static int lvl = 0, check_high_score = 0;
  int check_game = 0, check_current = 0;
  if (new_game)  // creating structure for tetris
  {
    FILE *file = fopen("brick_game/tetris/high_score.txt", "r+");
    check_game = init_object(&var, file);
    if (!check_game) {
      check_high_score = var.high_score;
    }
    if (file) {
      fclose(file);
    }
  }
  static figure current;
  if (new_current && !check_game)  // creating figure
  {
    memory_allocation_figure(&current);
    check_current = init_current_figure(&current, var.next);
  }
  if (check_current || check_game)  // if got some error, we return to interface
                                    // and to main loop error_memory
  {
    var.pause = Error_memory;
  }
  var = do_action(&var, &current, action, check_high_score, &lvl);
  return var;
}
int move_down(figure *var) {
  int res = 0;
  if (var) {
    var->y += 1;
  } else {
    res = 1;
  }
  return res;
}
int collision(GameInfo_t var, figure current) {
  int res = 0;
  for (int i = 0; i < VALUE_SAMPLE && !res; i++) {
    for (int j = 0; j < VALUE_SAMPLE; j++) {
      if (current.blocks[i][j] == 1) {
        int x = current.x + j;
        int y = current.y + (i - 1);
        if (x < 0 || x >= WIDTH_MAIN || y < 0 || y >= HEIGHT_MAIN) {
          res = 1;
        } else if (var.field[y][x] == 1) {
          res = 1;
        }
      }
    }
  }
  return res;
}
int move_up(figure *var) {
  int res = 0;
  if (var) {
    var->y -= 1;
  } else {
    res = 1;
  }
  return res;
}
int move_left(figure *var) {
  int res = 0;
  if (var) {
    var->x -= 1;
  } else {
    res = 1;
  }
  return res;
}
int move_right(figure *var) {
  int res = 0;
  if (var) {
    var->x += 1;
  } else {
    res = 1;
  }
  return res;
}
int put_current(GameInfo_t *var, figure current) {
  int res = 0;
  if (var) {
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      for (int j = 0; j < VALUE_SAMPLE; j++) {
        if (current.blocks[i][j] == 1) {
          int x = current.x + j;
          int y = current.y + (i - 1);
          var->field[y][x] = 1;
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}
int count_points(GameInfo_t *var) {
  int res = 0;
  int points[] = {0, 100, 300, 700, 1500};
  for (int i = HEIGHT_MAIN - 1; i >= 0; i--) {
    while (filled_line(i, var)) {
      move_upper_lines(i, var);
      res += 1;
    }
  }
  if (res > 4) {
    res = 4;
  }
  return points[res];
}
int filled_line(int i, GameInfo_t *var) {
  int res = 1;
  for (int j = 0; j < WIDTH_MAIN; j++) {
    if (var->field[i][j] == 0) {
      res = 0;
      break;
    }
  }
  return res;
}
int move_upper_lines(int i, GameInfo_t *var) {
  int res = 0;
  if (var) {
    if (i == 0) {
      for (int j = 0; j < WIDTH_MAIN; j++) {
        var->field[i][j] = 0;
      }
    } else {
      for (int k = i; k >= 1; k--) {
        for (int j = 0; j < WIDTH_MAIN; j++) {
          var->field[k][j] = var->field[k - 1][j];
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}
int update_score(GameInfo_t *var) {
  int res = 0;
  if (var) {
    var->high_score = var->score;
  } else {
    res = 1;
  }
  return res;
}
int create_new_figure(GameInfo_t *var, figure *current) {
  int res = 0;
  if (var && current) {
    init_current_figure(current, var->next);
    init_next_figure(var);
  } else {
    res = 1;
  }
  return res;
}
void free_figure(figure *var) {
  if (var) {
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      free(var->blocks[i]);
    }
    free(var->blocks);
  }
}
int memory_allocation_figure(figure *var) {
  int res = 0;
  if (var) {
    var->blocks = malloc(sizeof(int *) * VALUE_SAMPLE);
    if (var->blocks) {
      for (int i = 0; i < VALUE_SAMPLE; i++) {
        var->blocks[i] = calloc(VALUE_SAMPLE, sizeof(int));
        if (var->blocks[i] == NULL) {
          res = 1;
          break;
        }
      }
    } else {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}
int erase_field(GameInfo_t *var, figure current)  // erase figure from field
{
  int res = 0;
  if (var) {
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      for (int j = 0; j < VALUE_SAMPLE; j++) {
        if (current.blocks[i][j] == 1) {
          int x = current.x + j;
          int y = current.y + (i - 1);
          var->field[y][x] = 0;
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}
void userInput(UserAction_t action, bool hold) {
  (void)hold;
  switch (action) {
    case Left:
      static_storage(0, 0, Left);
      break;
    case Right:
      static_storage(0, 0, Right);
      break;
    case Down:
      static_storage(0, 0, Down);
      break;
    case Pause:
      static_storage(0, 0, Pause);
      break;
    case Terminate:
      static_storage(0, 0, Terminate);
      break;
    case Action:
      static_storage(0, 0, Action);
      break;
    case Start:
      static_storage(0, 0, Start);
      break;
  }
}
void free_in_the_end_of_game(GameInfo_t *var, figure *current) {
  if (var) {
    var->pause = End_of_game;
    free_field(var);
    free_next(var);
  }
  if (current) {
    free_figure(current);
  }
}
int rotate_figure(GameInfo_t *var, figure *current) {
  int res = 0;
  if (var && current) {
    figure tmp;
    tmp.x = current->x;
    tmp.y = current->y;
    memory_allocation_figure(&tmp);

    for (int i = 0; i < VALUE_SAMPLE; i++) {
      for (int j = 0; j < VALUE_SAMPLE; j++) {
        tmp.blocks[i][j] = current->blocks[j][VALUE_SAMPLE - 1 - i];
      }
    }
    if (!collision(*var, tmp) && square(current)) {
      for (int i = 0; i < VALUE_SAMPLE; i++) {
        for (int j = 0; j < VALUE_SAMPLE; j++) {
          current->blocks[i][j] = tmp.blocks[i][j];
        }
      }
    }
    free_figure(&tmp);
  } else {
    res = 1;
  }
  return res;
}
int clear_field(GameInfo_t *var) {
  int res = 0;
  if (var) {
    for (int i = 0; i < HEIGHT_MAIN; i++) {
      for (int j = 0; j < WIDTH_MAIN; j++) {
        var->field[i][j] = 0;
      }
    }
  } else {
    res = 1;
  }
  return res;
}
int writening_high_score(int score) {
  int res = 0;
  FILE *file = fopen("brick_game/tetris/high_score.txt", "r+");
  if (file) {
    fprintf(file, "%d", score);
    fclose(file);
  } else {
    res = 1;
  }
  return res;
}
int square(figure *figure)  // if figure is square, we don't need to rotate it
{
  int res = 0, k = 0, c = 1;
  if (!figure) {
    res = 1;
  } else {
    int square_coord[] = {1, 2, 1, 3, 2, 2, 2, 3};
    for (int i = 0; i < VALUE_SAMPLE; i++) {
      for (int j = 0; j < VALUE_SAMPLE; j++) {
        if (figure->blocks[i][j] == 1 && i == square_coord[k] &&
            j == square_coord[c]) {
          k += 2;
          c += 2;
        } else if (figure->blocks[i][j] == 1 &&
                   (i != square_coord[k] || j != square_coord[c])) {
          res = 2;
          break;
        }
      }
    }
  }
  return res;
}
GameInfo_t do_action(GameInfo_t *var, figure *current, UserAction_t action,
                     int check_high_score, int *lvl) {
  switch (action) {
    case Left:
      erase_field(var, *current);
      move_left(current);
      if (collision(*var, *current)) {
        move_right(current);
      }
      put_current(var, *current);
      break;
    case Right:
      erase_field(var, *current);
      move_right(current);
      if (collision(*var, *current)) {
        move_left(current);
      }
      put_current(var, *current);
      break;
    case Pause:
      if (var->pause == Game) {
        var->pause = Pause;
      } else {
        var->pause = Game;
      }
      break;
    case Terminate:
      if (var->score > check_high_score) {
        writening_high_score(var->score);
      }
      free_in_the_end_of_game(var, current);
      break;
    case Action:
      erase_field(var, *current);
      rotate_figure(var, current);
      put_current(var, *current);
      break;
    case Start:
      var->pause = Game;
      clear_field(var);
      init_ints(var);
      create_new_figure(var, current);
      put_current(var, *current);
      break;
    case Down:
      processing_down(var, current, lvl, check_high_score);
      break;
    default:
      break;
  }
  return *var;
}
void processing_down(GameInfo_t *var, figure *current, int *lvl,
                     int check_high_score) {
  int count_pts = 0;
  erase_field(var, *current);
  move_down(current);
  if (collision(*var, *current)) {
    move_up(current);
    put_current(var, *current);
    count_pts = count_points(var);
    var->score += count_pts;
    *lvl += count_pts;
    if (*lvl >= 600) {
      var->level += 1;
      var->speed += 1;
      *lvl = 0;
      var->pause = Change_level;  // if changed level, send info to main loop
                                  // change speed
    }
    if (var->score > var->high_score) {
      update_score(var);
    }
    create_new_figure(var, current);
    if (collision(*var, *current))  // if after creating new figure have
                                    // collision, it's end game situation
    {
      var->pause = Pre_exit_situation;
    }
  } else {
    put_current(var, *current);
  }
}
GameInfo_t get_info_extern() {
  GameInfo_t res = static_storage(0, 0, Up);
  return res;
}
