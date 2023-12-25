cmake_minimum_required(VERSION 3.27.9)

project(TugasAkhir1)

# EXTERNAL LIBRARIES
# set(CURSES_NEED_NCURSES, TRUE)
find_package(Curses REQUIRED)
set(CURSES_MENU_LIBRARY_PATH, "/usr/lib/libmenu.so")
set(CURSES_MENU_INCLUDE_PATH, "/usr/include/menu.h")
set(CURSES_PANEL_LIBRARY_PATH, "/usr/lib/libpanel.so")
set(CURSES_PANEL_INCLUDE_PATH, "/usr/include/panel.h")
add_link_options(-lpanel -lmenu -lncurses)

# LIBRARIES
add_library(contact_functions STATIC contact.c)
add_library(utility_functions STATIC utils.c)
add_library(contact_menu_functions STATIC contact_menu.c)

add_executable(tugasakhir main.c)

target_include_directories(tugasakhir PUBLIC ${CURSES_INCLUDE_DIRS} ${CURSES_MENU_INCLUDE_PATH} ${CURSES_PANEL_INCLUDE_PATH})

target_link_libraries(tugasakhir ${CURSES_LIBRARIES} ${CURSES_MENU_LIBRARY_PATH} ${CURSES_PANEL_LIBRARY_PATH} contact_functions utility_functions contact_menu_functions)