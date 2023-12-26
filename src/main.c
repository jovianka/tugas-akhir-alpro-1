#include <ncurses.h>
#include <menu.h>
#include <panel.h>
#include "contact.h"
#include "contact_menu.h"


int main() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);


	int y_max;
	int x_max;
	getmaxyx(stdscr, y_max, x_max);

	PANEL* contact_panels[3];
	PANEL* top;

	WINDOW* details_win = newwin(y_max / 1.2, 3 * x_max / 4 - 1, 1, x_max / 4 + 2);
	int y_details_win;
	int x_details_win;
	getmaxyx(details_win, y_details_win, x_details_win);
	box(details_win, 0, 0);
	mvwprintw(details_win, 0, x_details_win / 2 - 9, " DETAILS ");

	WINDOW* input_win = newwin(y_max / 1.2, 3 * x_max / 4 - 1, 1, x_max / 4 + 2);
	int y_input_win;
	int x_input_win;
	getmaxyx(input_win, y_input_win, x_input_win);
	box(input_win, 0, 0);
	mvwprintw(input_win, 0, x_input_win / 2 - 7, " INPUT ");

	WINDOW* contact_win = newwin(y_max / 1.2, x_max / 4, 1, 2);
	int y_contact_win;
	int x_contact_win;
	getmaxyx(contact_win, y_contact_win, x_contact_win);
	box(contact_win, 0, 0);
	mvwprintw(contact_win, 0, x_contact_win / 2 - 11, " CONTACT MANAGER WOW! ");

	mvprintw(LINES - 2, 3, "A: Add Contact\tF: Search Contacts\tE: Edit Contact\t\tD: Delete Contact\tQ: Quit");
	
	contact_panels[0] = new_panel(contact_win);
	contact_panels[1] = new_panel(input_win);
	contact_panels[2] = new_panel(details_win);

	init_pair(1, COLOR_CYAN, COLOR_YELLOW);
	init_pair(2, COLOR_RED, COLOR_BLACK);

	keypad(contact_win, TRUE);
	int quit = 0;
	char search_term[255] = "";
	int searched_count;
	MENU* contact_menu;
	Contact* searched_contacts;
	int* searched_contact_indices;
	ITEM** contact_items;


	searched_count = get_search_count(search_term);
	searched_contact_indices = search_and_get_contact_indices(search_term);
	searched_contacts = search_and_get_contacts(search_term);
	contact_items = get_searched_contact_items(searched_contacts, searched_contact_indices, searched_count);
	contact_menu = new_wmenu(contact_win, contact_items, contact_menu);

	post_menu(contact_menu);
	update_panels();
	doupdate();

	top = contact_panels[2];

	while (quit != 1) {
		if (searched_count != 0) {
			ITEM* cur_item = current_item(contact_menu);
			int* cur_contact_index = item_userptr(cur_item);
			display_details(details_win, *cur_contact_index);
		} else {
			wclear(details_win);
			box(details_win, 0, 0);
			mvwprintw(details_win, 0, x_details_win / 2 - 9, " DETAILS ");
			wrefresh(details_win);
		}

		int ch = wgetch(contact_win);

		switch (ch) {
			case 'q':
			case 'Q':
				quit = 1;
				break;

			case 'f':
			case 'F':
				wmove(contact_win, y_contact_win - 2, 0);
				wclrtoeol(contact_win);
				box(contact_win, 0, 0);
				mvwprintw(contact_win, 0, x_contact_win / 2 - 11, " CONTACT MANAGER WOW! ");

				echo();
				curs_set(1);
				wattron(contact_win, COLOR_PAIR(1));
				mvwprintw(contact_win, y_contact_win - 2, 2, "Search: ");
				mvwgetnstr(contact_win, y_contact_win - 2, 10, search_term, 255);
				wattroff(contact_win, COLOR_PAIR(1));
				curs_set(0);
				noecho();

				free_menu_full(contact_menu, contact_items, searched_count);
				free(searched_contacts);
				free(searched_contact_indices);

				searched_count = get_search_count(search_term);
				searched_contact_indices = search_and_get_contact_indices(search_term);
				searched_contacts = search_and_get_contacts(search_term);
				contact_items = get_searched_contact_items(searched_contacts, searched_contact_indices, searched_count);
				contact_menu = new_wmenu(contact_win, contact_items, contact_menu);

				post_menu(contact_menu);

				if (searched_count == 0) {
					wmove(contact_win, y_contact_win - 2, 0);
					wclrtoeol(contact_win);
					mvwprintw(contact_win, y_contact_win - 2, 2, "No results found");
				} else {
					mvwprintw(contact_win, y_contact_win - 2, 10, search_term);
				}

				box(contact_win, 0, 0);
				mvwprintw(contact_win, 0, x_contact_win / 2 - 11, " CONTACT MANAGER WOW! ");

				doupdate();
				break;


			case 'a':
			case 'A':
				wmove(input_win, 2, 2);
				wclrtoeol(input_win);
				wmove(input_win, 3, 2);
				wclrtoeol(input_win);
				wmove(input_win, 4, 2);
				wclrtoeol(input_win);
				wmove(input_win, 5, 2);
				wclrtoeol(input_win);
				wmove(input_win, 6, 2);
				wclrtoeol(input_win);
				wmove(input_win, 7, 2);
				wclrtoeol(input_win);
				box(input_win, 0, 0);
				mvwprintw(input_win, 0, x_input_win / 2 - 11, " ADDING A NEW CONTACT ");

				echo();
				curs_set(1);
				wattron(input_win, COLOR_PAIR(1));

				Contact new_contact;
				strncpy(new_contact.name, "", 255);
				strncpy(new_contact.phone_number, "", 15);
				strncpy(new_contact.email, "", 320);
				strncpy(new_contact.address, "", 255);
				strncpy(new_contact.website, "", 255);
				strncpy(new_contact.birthday, "", 31);
				top_panel(contact_panels[1]);

				mvwprintw(input_win, 2, 2, "Name: ");
				mvwprintw(input_win, 3, 2, "Number: ");
				mvwprintw(input_win, 4, 2, "Email: ");
				mvwprintw(input_win, 5, 2, "Address: ");
				mvwprintw(input_win, 6, 2, "Website: ");
				mvwprintw(input_win, 7, 2, "Birthday: ");
				while (strlen(new_contact.name) == 0) {
					wattron(input_win, COLOR_PAIR(2));
					mvwprintw(input_win, 2, x_details_win - 28, "This field must be filled!");
					wattroff(input_win, COLOR_PAIR(2));
					mvwgetnstr(input_win, 2, 8, new_contact.name, 255);
				}
				while (strlen(new_contact.phone_number) == 0) {
					wattron(input_win, COLOR_PAIR(2));
					mvwprintw(input_win, 3, x_details_win - 28, "This field must be filled!");
					wattroff(input_win, COLOR_PAIR(2));
					mvwgetnstr(input_win, 3, 10, new_contact.phone_number, 15);
				}
				mvwgetnstr(input_win, 4, 9, new_contact.email, 320);
				mvwgetnstr(input_win, 5, 11, new_contact.address, 255);
				mvwgetnstr(input_win, 6, 11, new_contact.website, 255);
				mvwgetnstr(input_win, 7, 12, new_contact.birthday, 31);

				wattroff(input_win, COLOR_PAIR(1));
				curs_set(0);
				noecho();

				add_contact(new_contact);
				top_panel(contact_panels[2]);
				
				free_menu_full(contact_menu, contact_items, searched_count);
				free(searched_contacts);
				free(searched_contact_indices);

				strncpy(search_term, "", 255);
				searched_count = get_search_count(search_term);
				searched_contact_indices = search_and_get_contact_indices(search_term);
				searched_contacts = search_and_get_contacts(search_term);
				contact_items = get_searched_contact_items(searched_contacts, searched_contact_indices, searched_count);
				contact_menu = new_wmenu(contact_win, contact_items, contact_menu);

				post_menu(contact_menu);
				box(contact_win, 0, 0);
				mvwprintw(contact_win, 0, x_contact_win / 2 - 11, " CONTACT MANAGER WOW! ");
				break;


			case 'e':
			case 'E':
				if (searched_count > 0) {
					ITEM* cur_item = current_item(contact_menu);
					int* cur_contact_index = item_userptr(cur_item);

					FILE* file = fopen("contact_data.dat", "rb");
					Contact current_contact;

					fseek(file, (*cur_contact_index - 1) * sizeof(Contact), SEEK_SET);
					fread(&current_contact, sizeof(Contact), 1, file);

					fclose(file);

					echo();
					curs_set(1);
					wattron(details_win, COLOR_PAIR(1));

					Contact edited_contact;
					strncpy(edited_contact.name, "", 255);
					strncpy(edited_contact.phone_number, "", 15);
					strncpy(edited_contact.email, "", 320);
					strncpy(edited_contact.address, "", 255);
					strncpy(edited_contact.website, "", 255);
					strncpy(edited_contact.birthday, "", 31);

					while (strlen(edited_contact.name) == 0) {
						wmove(details_win, 2, 2);
						wclrtoeol(details_win);
						box(details_win, 0, 0);
						wattron(details_win, COLOR_PAIR(2));
						mvwprintw(details_win, 2, x_details_win - 28, "This field must be filled!");
						wattroff(details_win, COLOR_PAIR(2));
						mvwprintw(details_win, 0, x_details_win / 2 - 11, " EDITING {%s} ", current_contact.name);
						mvwprintw(details_win, 2, 2, "Name: ");
						mvwgetnstr(details_win, 2, 8, edited_contact.name, 255);
					}
					while (strlen(edited_contact.phone_number) == 0) {
						wmove(details_win, 3, 2);
						wclrtoeol(details_win);
						box(details_win, 0, 0);
						wattron(details_win, COLOR_PAIR(2));
						mvwprintw(details_win, 3, x_details_win - 28, "This field must be filled!");
						wattroff(details_win, COLOR_PAIR(2));
						mvwprintw(details_win, 0, x_details_win / 2 - 11, " EDITING {%s} ", current_contact.name);
						mvwprintw(details_win, 3, 2, "Number: ");
						mvwgetnstr(details_win, 3, 10, edited_contact.phone_number, 15);
					}
					wmove(details_win, 4, 2);
					wclrtoeol(details_win);
					box(details_win, 0, 0);
					mvwprintw(details_win, 0, x_details_win / 2 - 11, " EDITING {%s} ", current_contact.name);
					mvwprintw(details_win, 4, 2, "Email: ");
					mvwgetnstr(details_win, 4, 9, edited_contact.email, 320);

					wmove(details_win, 5, 2);
					wclrtoeol(details_win);
					box(details_win, 0, 0);
					mvwprintw(details_win, 0, x_details_win / 2 - 11, " EDITING {%s} ", current_contact.name);
					mvwprintw(details_win, 5, 2, "Address: ");
					mvwgetnstr(details_win, 5, 11, edited_contact.address, 255);

					wmove(details_win, 6, 2);
					wclrtoeol(details_win);
					box(details_win, 0, 0);
					mvwprintw(details_win, 0, x_details_win / 2 - 11, " EDITING {%s} ", current_contact.name);
					mvwprintw(details_win, 6, 2, "Website: ");
					mvwgetnstr(details_win, 6, 11, edited_contact.website, 255);

					wmove(details_win, 7, 2);
					wclrtoeol(details_win);
					box(details_win, 0, 0);
					mvwprintw(details_win, 0, x_details_win / 2 - 11, " EDITING {%s} ", current_contact.name);
					mvwprintw(details_win, 7, 2, "Birthday: ");
					mvwgetnstr(details_win, 7, 12, edited_contact.birthday, 31);


					wattroff(details_win, COLOR_PAIR(1));
					curs_set(0);
					noecho();

					modify_contact(*cur_contact_index, edited_contact);
					
					free_menu_full(contact_menu, contact_items, searched_count);
					free(searched_contacts);
					free(searched_contact_indices);

					searched_count = get_search_count(search_term);
					searched_contact_indices = search_and_get_contact_indices(search_term);
					searched_contacts = search_and_get_contacts(search_term);
					contact_items = get_searched_contact_items(searched_contacts, searched_contact_indices, searched_count);
					contact_menu = new_wmenu(contact_win, contact_items, contact_menu);

					post_menu(contact_menu);
					box(contact_win, 0, 0);
					mvwprintw(contact_win, 0, x_contact_win / 2 - 11, " CONTACT MANAGER WOW! ");
				}
				break;


			case 'd':
			case 'D':
				if (searched_count > 0) {
					ITEM* cur_item = current_item(contact_menu);
					int* cur_contact_index = item_userptr(cur_item);
					delete_contact(*cur_contact_index);

					free_menu_full(contact_menu, contact_items, searched_count);
					free(searched_contacts);
					free(searched_contact_indices);

					searched_count = get_search_count(search_term);
					searched_contact_indices = search_and_get_contact_indices(search_term);
					searched_contacts = search_and_get_contacts(search_term);
					contact_items = get_searched_contact_items(searched_contacts, searched_contact_indices, searched_count);
					contact_menu = new_wmenu(contact_win, contact_items, contact_menu);

					post_menu(contact_menu);
					box(contact_win, 0, 0);
					mvwprintw(contact_win, 0, x_contact_win / 2 - 11, " CONTACT MANAGER WOW! ");
					
					doupdate();
				}
				break;


			case KEY_UP:
				menu_driver(contact_menu, REQ_UP_ITEM);
				break;


			case KEY_DOWN:
				menu_driver(contact_menu, REQ_DOWN_ITEM);
				break;
		}
		wrefresh(contact_win);
	}

	free_menu_full(contact_menu, contact_items, searched_count);
	free(searched_contacts);
	free(searched_contact_indices);
	endwin();

	return 0;
}
