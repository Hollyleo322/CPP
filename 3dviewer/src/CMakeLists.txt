cmake_minimum_required(VERSION 3.5...3.20)

project(3D_Viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск библиотек Qt, OpenGL
find_package(OpenGL)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)


# Поиск библоитеки Gtest
find_package(GTest REQUIRED)

add_library(3D_Viewer_backend STATIC 
    ./back/data_figure.cpp
    ./back/facade.cpp
    ./back/parser.cpp
    ./back/scene.cpp
    ./back/transform.cpp
    ./controller/control.cpp
)

target_link_libraries(3D_Viewer_backend PRIVATE )


set(3D_VIEWER_FRONTEND_SOURCES
   
    ./front/main.cpp
    ./front/mainwindow.h
    ./front/mainwindow.cpp
    ./front/mainwindow.ui
    ./front/viewport.cpp
    ./front/gif.h
    ./front/resources.qrc
)

qt_add_executable(3D_Viewer 
    MANUAL_FINALIZATION
    ${3D_VIEWER_FRONTEND_SOURCES}
)

target_link_libraries(3D_Viewer PRIVATE 3D_Viewer_backend OpenGL::GL Qt6::OpenGLWidgets)


qt_finalize_executable(3D_Viewer)

# Тесты

enable_testing()

add_executable(transform_tests
    ./back/tests/transform_test.cpp
)
target_link_libraries(transform_tests PRIVATE 3D_Viewer_backend GTest::gtest_main)
add_test(transform_test transform_tests)

add_executable(data_figure_tests
    ./back/tests/data_figure_test.cpp
)
target_link_libraries(data_figure_tests PRIVATE 3D_Viewer_backend GTest::gtest_main)
add_test(data_figure_test data_figure_tests)

add_executable(facade_tests
    ./back/tests/facade_test.cpp
)
target_compile_definitions(facade_tests PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/back/tests")
target_link_libraries(facade_tests PRIVATE 3D_Viewer_backend GTest::gtest_main)
add_test(facade_test facade_tests)