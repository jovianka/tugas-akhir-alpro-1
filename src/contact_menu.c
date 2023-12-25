#include "contact.h"
#include "contact_menu.h"

ITEM** get_searched_contact_items(Contact* searched_contacts, int* searched_indices, int searched_count) {
	ITEM** contact_items = (ITEM**)calloc((searched_count + 1), sizeof(ITEM*));

	for (int i = 0; i < searched_count; i++) {
		contact_items[i] = new_item(searched_contacts[i].name, searched_contacts[i].phone_number);
    set_item_userptr(contact_items[i], &(searched_indices[i]));
	}
	contact_items[searched_count] = (ITEM*)NULL;

  return contact_items; 
}

void free_menu_full(MENU* menu, ITEM** items, int items_count) {
    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < items_count; i++) {
      free_item(items[i]);
    }
    free(items);
}

MENU* new_wmenu(WINDOW* win, ITEM** items, MENU* menuptr) {
	menuptr = new_menu((ITEM**)items);
	int y_contact_win;
	int x_contact_win;
	getmaxyx(win, y_contact_win, x_contact_win);
	set_menu_win(menuptr, win);
	set_menu_sub(menuptr, derwin(win, y_contact_win - 5, x_contact_win - 2, 2, 1));
	set_menu_mark(menuptr, " - ");
  set_menu_format(menuptr, y_contact_win - 5, 1);

  return menuptr;
}

void display_details(WINDOW* win, int contact_index) {
	FILE* file = fopen("contact_data.dat", "rb");
	Contact current_contact;

	fseek(file, (contact_index - 1) * sizeof(Contact), SEEK_SET);
	fread(&current_contact, sizeof(Contact), 1, file);

	wmove(win, 2, 2);
	wclrtoeol(win);
	wmove(win, 3, 2);
	wclrtoeol(win);
	wmove(win, 4, 2);
	wclrtoeol(win);
	wmove(win, 5, 2);
	wclrtoeol(win);
	wmove(win, 6, 2);
	wclrtoeol(win);
	wmove(win, 7, 2);
	wclrtoeol(win);
	int y_details_win;
	int x_details_win;
	getmaxyx(win, y_details_win, x_details_win);
	box(win, 0, 0);
	mvwprintw(win, 0, x_details_win / 2 - 9, " DETAILS ");

	mvwprintw(win, 2, 2, "Name: %s", current_contact.name);
	mvwprintw(win, 3, 2, "Number: %s", current_contact.phone_number);
	mvwprintw(win, 4, 2, "Email: %s", current_contact.email);
	mvwprintw(win, 5, 2, "Address: %s", current_contact.address);
	mvwprintw(win, 6, 2, "Website: %s", current_contact.website);
	mvwprintw(win, 7, 2, "Birthday: %s", current_contact.birthday);

	update_panels();

	doupdate();


	fclose(file);
}