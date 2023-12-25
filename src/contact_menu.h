#include <ncurses.h>
#include <menu.h>

ITEM** get_searched_contact_items(Contact* searched_contacts, int* searched_contact_indices, int searched_count);
void free_menu_full(MENU* menu, ITEM** items, int items_count);
MENU* new_wmenu(WINDOW* win, ITEM** items, MENU* menuptr);
void display_details(WINDOW* win, int contact_index);