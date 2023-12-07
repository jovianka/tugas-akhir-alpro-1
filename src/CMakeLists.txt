cmake_minimum_required(VERSION 3.27.9)

project(TugasAkhir1)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(tugasakhir main.c)
target_link_libraries(tugasakhir ${CURSES_LIBRARIES})