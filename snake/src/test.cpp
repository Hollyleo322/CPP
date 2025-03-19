#include <gtest/gtest.h>

#include "brick_game/snake/snake.h"
#include "gui/cli/main.h"
using namespace s21;
TEST(snake, constructor) {
  Snake var;
  ASSERT_EQ(0, var.get_apple());
  ASSERT_EQ(5, var.get_direction());
  auto check_body = var.get_body();
  ASSERT_EQ(4, check_body.size());
  ASSERT_EQ(false, check_body.empty());
}
TEST(snake, set_field) {
  Snake var;
  std::vector<std::pair<int, int>> test = {{1, 2}, {3, 4}, {5, 6}};
  var.set_field(test);
  auto check_field = var.get_value_info();
  for (auto it = test.begin(); it != test.end(); ++it) {
    ASSERT_EQ(check_field.field[it->first][it->second], 1);
  }
}
TEST(snake, to_zero_field) {
  Snake var;
  std::vector<std::pair<int, int>> test = {{1, 2}, {3, 4}, {5, 6}};
  var.set_field(test);
  auto check_field = var.get_value_info();
  var.to_zero_field();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      ASSERT_EQ(check_field.field[i][j], 0);
    }
  }
}
TEST(snake, get_value_info) {
  Snake var;
  auto check_info = var.get_value_info();
  ASSERT_EQ(check_info.score, 0);
  ASSERT_EQ(check_info.level, 1);
  ASSERT_EQ(check_info.speed, 1);
  ASSERT_EQ(check_info.pause, 0);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      ASSERT_EQ(check_info.field[i][j], 0);
    }
  }
  ASSERT_EQ(check_info.next, nullptr);
}
TEST(snake, get_info) {
  Snake var;
  auto check_info = var.get_info();
  ASSERT_EQ(check_info->score, 0);
  ASSERT_EQ(check_info->level, 1);
  ASSERT_EQ(check_info->speed, 1);
  ASSERT_EQ(check_info->pause, 0);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      ASSERT_EQ(check_info->field[i][j], 0);
    }
  }
  ASSERT_EQ(check_info->next, nullptr);
}
TEST(snake, set_dir) {
  Snake var;
  var.set_direction(5);
  ASSERT_EQ(5, var.get_direction());
}
TEST(snake, set_apple) {
  Snake var;
  var.set_apple(5);
  ASSERT_EQ(5, var.get_apple());
}
TEST(snake, in_body_apple_fls) {
  Snake var;
  ASSERT_EQ(false, var.in_body_apple());
}
TEST(snake, in_body_apple_true) {
  Snake var;
  var.set_apple(45);
  ASSERT_EQ(true, var.in_body_apple());
}
TEST(snake, in_body_head_tr) {
  Snake var;
  std::vector<std::pair<int, int>> test = {{1, 2}, {2, 2}, {1, 2}};
  var.set_body(test);
  ASSERT_EQ(true, var.in_body_head());
}
TEST(snake, in_body_head_fls) {
  Snake var;
  ASSERT_EQ(false, var.in_body_head());
}
TEST(snake, reset) {
  Snake var;
  var.set_apple(45);
  var.set_direction(122);
  var.reset_game();
  ASSERT_EQ(5, var.get_direction());
  auto check_body = var.get_body();
  ASSERT_EQ(4, check_body.size());
  ASSERT_EQ(false, check_body.empty());
}
TEST(snake, set_body) {
  Snake var;
  std::vector<std::pair<int, int>> test = {{1, 2}, {2, 2}};
  var.set_body(test);
  auto it2 = test.begin();
  for (auto it = var.get_body().begin(); it != var.get_body().end();
       it++, it2++) {
    ASSERT_EQ(it2->first, it->first);
  }
}
TEST(snake, check_snake_first) {
  Snake var;
  var.set_apple(45);
  std::pair<int, int> end = {7, 5};
  var.check_snake(end);
  auto test = var.get_info();
  ASSERT_EQ(test->score, 1);
  ASSERT_EQ(var.get_body().size(), 5);
}
TEST(snake, check_snake_second) {
  Snake var;
  std::vector<std::pair<int, int>> test = {{-1, 2}, {0, 2}};
  std::pair<int, int> end = {1, 2};
  var.set_body(test);
  var.check_snake(end);
  auto test2 = var.get_info();
  ASSERT_EQ(test2->pause, Pre_exit_situation);
}
TEST(snake, check_snake_third) {
  Snake var;
  std::vector<std::pair<int, int>> test = {{1, 2}, {2, 2}, {1, 2}};
  std::pair<int, int> end = {3, 2};
  var.set_body(test);
  var.check_snake(end);
  auto test2 = var.get_info();
  ASSERT_EQ(test2->pause, Pre_exit_situation);
}
TEST(snake, check_snake_fourth) {
  Snake var;
  var.set_apple(45);
  std::pair<int, int> end = {7, 5};
  auto test = var.get_info();
  test->score = 199;
  var.check_snake(end);
  ASSERT_EQ(test->pause, Win);
}
TEST(snake, check_snake_fith) {
  Snake var;
  var.set_apple(45);
  std::pair<int, int> end = {7, 5};
  auto test = var.get_info();
  test->score = 4;
  var.check_snake(end);
  ASSERT_EQ(test->level, 2);
}
TEST(snake, left) {
  Snake var;
  ASSERT_EQ(Left, var.processing_left());
  ASSERT_EQ(Down, var.processing_left());
  ASSERT_EQ(Right, var.processing_left());
  ASSERT_EQ(Up, var.processing_left());
}
TEST(snake, right) {
  Snake var;
  ASSERT_EQ(Right, var.processing_right());
  ASSERT_EQ(Down, var.processing_right());
  ASSERT_EQ(Left, var.processing_right());
  ASSERT_EQ(Up, var.processing_right());
}
TEST(snake, change_lvl) {
  Snake var;
  var.change_level();
  auto test = var.get_info();
  ASSERT_EQ(test->level, 2);
  test->level = 10;
  var.change_level();
  ASSERT_EQ(test->level, 10);
}
TEST(snake, update) {
  auto var = get_snake();
  userInput(Left, false);
  ASSERT_EQ(Left, var->get_direction());
  userInput(Right, false);
  ASSERT_EQ(Up, var->get_direction());
  userInput(Pause, false);
  ASSERT_EQ(Pause, var->get_info()->pause);
  userInput(Start, false);
  ASSERT_EQ(Up, var->get_direction());
  auto check_body = var->get_body();
  ASSERT_EQ(4, check_body.size());
  ASSERT_EQ(false, check_body.empty());
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
