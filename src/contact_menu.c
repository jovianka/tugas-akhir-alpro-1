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
	wrefresh(win);


	fclose(file);
}


// void edit_form(WINDOW* win, int contact_index) {
// 	init_pair(1, COLOR_CYAN, COLOR_YELLOW);
// 	FILE* file = fopen("contact_data.dat", "rb");
// 	Contact current_contact;

// 	fseek(file, (contact_index - 1) * sizeof(Contact), SEEK_SET);
// 	fread(&current_contact, sizeof(Contact), 1, file);

// 	fclose(file);

// 	Contact edited_contact;
// 	strncpy(edited_contact.name, current_contact.name, 255);
// 	strncpy(edited_contact.phone_number, current_contact.phone_number, 15);
// 	strncpy(edited_contact.email, current_contact.email, 320);
// 	strncpy(edited_contact.address, current_contact.address, 255);
// 	strncpy(edited_contact.website, current_contact.website, 255);
// 	strncpy(edited_contact.birthday, current_contact.birthday, 31);

// 	FIELD *fields[7];
// 	FORM  *form;
// 	int y_win;
// 	int x_win;
// 	getmaxyx(win, y_win, x_win);

// 	fields[0] = new_field(1, 32, 0, 12, 6, 31);
// 	fields[1] = new_field(1, 15, 1, 12, 0, 0);
// 	fields[2] = new_field(1, 32, 2, 12, 9, 0);
// 	fields[3] = new_field(1, 32, 3, 12, 6, 31);
// 	fields[4] = new_field(1, 32, 4, 12, 6, 31);
// 	fields[5] = new_field(1, 31, 5, 12, 0, 0);
// 	fields[6] = NULL;

// 	set_field_buffer(fields[0], 0, edited_contact.name);
// 	set_field_buffer(fields[1], 0, edited_contact.phone_number);
// 	set_field_buffer(fields[2], 0, edited_contact.email);
// 	set_field_buffer(fields[3], 0, edited_contact.address);
// 	set_field_buffer(fields[4], 0, edited_contact.website);
// 	set_field_buffer(fields[5], 0, edited_contact.birthday);

// 	for (int i = 0; i < 6; i++) {
// 		set_field_back(fields[i], A_UNDERLINE);
// 		field_opts_off(fields[i], O_AUTOSKIP);
// 		set_field_type(fields[i], TYPE_ALNUM);
// 	}


// 	form = new_form(fields);

// 	keypad(win, TRUE);
// 	set_form_win(form, win);
// 	set_form_sub(form, derwin(win, y_win - 3, x_win - 2, 2, 1));
// 	wclear(win);
// 	box(win, 0, 0);
// 	mvwprintw(win, 0, x_win / 2 - strlen(current_contact.name) / 2 - 6, " EDITING {%s} ", current_contact.name);
// 	post_form(form);
// 	set_current_field(form, fields[0]); /* Set focus to the colored field */
// 	mvwprintw(win, 2, 2, "Name: ");
// 	mvwprintw(win, 3, 2, "Number: ");
// 	mvwprintw(win, 4, 2, "Email: ");
// 	mvwprintw(win, 5, 2, "Address: ");
// 	mvwprintw(win, 6, 2, "Website: ");
// 	mvwprintw(win, 7, 2, "Birthday: ");
// 	wmove(win, 2, 13);
// 	wrefresh(win);


// 	echo();
// 	curs_set(1);
// 	wattron(win, COLOR_PAIR(1));
// 	int cancel = 0;
// 	int submitted = 0;
// 	while (cancel != 1 && submitted != 1) {
// 		int ch = wgetch(win);
// 		switch (ch) {
// 			case KEY_DOWN:
// 				form_driver(form, REQ_NEXT_FIELD);
// 				form_driver(form, REQ_END_LINE);
// 				break;

// 			case KEY_UP:
// 				form_driver(form, REQ_PREV_FIELD);
// 				form_driver(form, REQ_END_LINE);
// 				break;

// 			case KEY_LEFT:
// 				form_driver(form, REQ_PREV_CHAR);
// 				break;

// 			case KEY_RIGHT:
// 				form_driver(form, REQ_NEXT_CHAR);
// 				break;

// 			// Delete the char before cursor
// 			case KEY_BACKSPACE:
// 			case 127:
// 				form_driver(form, REQ_DEL_PREV);
// 				break;

// 			// Delete the char under the cursor
// 			case KEY_DC:
// 				form_driver(form, REQ_DEL_CHAR);
// 				break;

// 			case 10:
// 				form_driver(form, REQ_VALIDATION);
				
// 				strncpy(edited_contact.name, trim_whitespaces(field_buffer(fields[0], 0)), 255);
// 				strncpy(edited_contact.phone_number, trim_whitespaces(field_buffer(fields[1], 0)), 15);
// 				strncpy(edited_contact.email, trim_whitespaces(field_buffer(fields[2], 0)), 320);
// 				strncpy(edited_contact.address, trim_whitespaces(field_buffer(fields[3], 0)), 255);
// 				strncpy(edited_contact.website, trim_whitespaces(field_buffer(fields[4], 0)), 255);
// 				strncpy(edited_contact.birthday,trim_whitespaces(field_buffer(fields[5], 0)), 31);
// 				modify_contact(contact_index, edited_contact);

// 				unpost_form(form);
// 				free_form(form);
// 				for (int i = 0; i < 6; i++) {
// 					free_field(fields[i]);
// 				}
// 				submitted = 1;

// 			default:
// 				form_driver(form, ch);
// 				break;

// 		}
// 		wrefresh(win);

// 	}
// 	wattroff(win, COLOR_PAIR(1));
// 	curs_set(0);
// 	noecho();

// }