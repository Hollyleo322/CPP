#pragma once
#include <vector>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include <fstream>
#include <iostream>
#include "../../gui/cli/main.h"
#define WIDTH 10
#define HEIGHT 20
namespace s21
{
    class game_window;
    typedef struct Snake
    {
    private:
        char direction;
        std::vector<std::pair<int, int>> body;
        unsigned apple;
        GameInfo_t *info;

    public:
        Snake();
        ~Snake();
        void set_field(const std::vector<std::pair<int, int>> &body)
        {
            for (auto it = body.begin(); it != body.end(); it++)
            {
                info->field[it->first][it->second] = 1;
            }
            info->field[apple / 10][apple % 10] = 1;
        }
        void to_zero_field();
        GameInfo_t *get_info() const { return info; }
        GameInfo_t get_value_info() const { return *info; }
        void set_direction(const char &var) { this->direction = var; }
        void set_apple(const unsigned &var) { this->apple = var; }
        void set_body(const std::vector<std::pair<int, int>> &body) { this->body = body; }
        char get_direction() const { return this->direction; }
        std::vector<std::pair<int, int>> &get_body() { return this->body; }
        unsigned get_apple() const { return this->apple; }
        bool in_body_apple();
        bool in_body_head();
        void reset_game();
        void generate_apple();
        void check_snake(const std::pair<int, int> &end);
        int processing_left();
        int processing_right();
        void change_level();
    } Snake;
    extern "C" Snake *get_snake();
    extern "C" GameInfo_t get_info_extern();
    extern "C" GameInfo_t updateCurrentState();
    extern "C" void userInput(UserAction_t action, bool hold);
    extern "C" void main_game();
} // namespace s21
