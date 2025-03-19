#pragma once
typedef enum
{
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct
{
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef enum
{
    Game,
    Pause_game,
    Error_memory,
    End_of_game,
    Change_level,
    Win,
    Pre_exit_situation
} ConditionGame;