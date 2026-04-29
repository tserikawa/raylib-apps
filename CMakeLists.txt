cmake_minimum_required(VERSION 3.20)
project(MyApp C)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

set(DRAWING_SOURCES
    apps/drawing/main.c
    apps/drawing/button.c
    apps/drawing/edit_mode.c
    apps/drawing/line2.c
)
add_executable(drawing-app ${DRAWING_SOURCES})
target_link_libraries(drawing-app raylib)