cmake_minimum_required(VERSION 3.27.9)

project(TugasAkhir1)

# EXTERNAL LIBRARIES
find_package(Curses REQUIRED)

# LIBRARIES
add_library(contact_functions STATIC contact.c)

add_executable(tugasakhir main.c)

target_include_directories(tugasakhir PUBLIC ${CURSES_INCLUDE_DIRS})

target_link_libraries(tugasakhir ${CURSES_LIBRARIES})
target_link_libraries(tugasakhir contact_functions)