cmake_minimum_required(VERSION 3.5)

project(s21_snake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
option(snake "snake enabled" ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)


if (snake)
    project(s21_snake VERSION 0.1 LANGUAGES CXX)
    add_executable(s21_snake
    game_window.cpp
    main_desktop.cpp
    mainwindows21snake.cpp
)
    target_link_libraries(s21_snake
        Qt6::Widgets)
    add_definitions(-Dsnake)
    target_link_libraries(s21_snake ${CMAKE_CURRENT_SOURCE_DIR}/s21_snake.a)
else()
    project(s21_tetris VERSION 0.1 LANGUAGES CXX)
    add_executable(s21_tetris
    game_window.cpp
    main_desktop.cpp
    mainwindows21snake.cpp
    )
    target_link_libraries(s21_tetris
        Qt6::Widgets)
    target_link_libraries(s21_tetris ${CMAKE_CURRENT_SOURCE_DIR}/s21_tetris.a)
endif()
