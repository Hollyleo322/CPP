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

# include(FetchContent)

# FetchContent_Declare(
# 	glm
# 	GIT_REPOSITORY	https://github.com/g-truc/glm.git
# 	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
# )

# FetchContent_MakeAvailable(glm)

# enable_testing()

# add_executable(transform_tests
#     ./back/tests/transform_test.cpp
#     ./back/transform.cpp
#     ./back/data_figure.cpp
# )

# target_link_libraries(transform_tests PRIVATE GTest::gtest_main glm::glm )

add_test(transform_test transform_tests)