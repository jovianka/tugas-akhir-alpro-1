// #include <curses.h>
// #include <menu.h>

// #define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
// #define CTRLD 	4

// char *choices[] = {
//                         "Choice 1",
//                         "Choice 2",
//                         "Choice 3",
//                         "Choice 4",
//                         "Exit",
//                   };

// int main()
// {	ITEM **my_items;
// 	int c;				
// 	MENU *my_menu;
// 	int n_choices, i;
// 	ITEM *cur_item;
	
	
// 	initscr();
// 	cbreak();
// 	noecho();
// 	keypad(stdscr, TRUE);
	
// 	n_choices = ARRAY_SIZE(choices);
// 	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

// 	for(i = 0; i < n_choices; ++i)
// 	        my_items[i] = new_item(choices[i], choices[i]);
// 	my_items[n_choices] = (ITEM *)NULL;

// 	my_menu = new_menu((ITEM **)my_items);
// 	mvprintw(LINES - 2, 0, "F1 to Exit");
// 	post_menu(my_menu);
// 	refresh();

// 	while((c = getch()) != KEY_F(1))
// 	{   switch(c)
// 	    {	case KEY_DOWN:
// 		        menu_driver(my_menu, REQ_DOWN_ITEM);
// 				break;
// 			case KEY_UP:
// 				menu_driver(my_menu, REQ_UP_ITEM);
// 				break;
// 		}
// 	}	

// 	free_item(my_items[0]);
// 	free_item(my_items[1]);
// 	free_menu(my_menu);
// 	endwin();
// }
#include <form.h>

int main()
{	FIELD *field[3];
	FORM  *my_form;
	int ch;
	
	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize few color pairs */
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);

	/* Initialize the fields */
	field[0] = new_field(1, 10, 4, 18, 50, 12);
	field[1] = new_field(1, 10, 6, 18, 0, 0);
	field[2] = NULL;

	/* Set field options */
	set_field_fore(field[0], COLOR_PAIR(1));/* Put the field with blue background */
	set_field_back(field[0], COLOR_PAIR(2));/* and white foreground (characters */
						/* are printed in white 	*/
	field_opts_off(field[0], O_AUTOSKIP);  	/* Don't go to next field when this */
						/* Field is filled up 		*/
	set_field_back(field[1], A_UNDERLINE); 
	field_opts_off(field[1], O_AUTOSKIP);

	/* Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();
	
	set_current_field(my_form, field[0]); /* Set focus to the colored field */
	mvprintw(4, 10, "Value 1:");
	mvprintw(6, 10, "Value 2:");
	mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys to switch between fields");
	refresh();

	/* Loop through to get user requests */
	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_LEFT:
				form_driver(my_form, REQ_PREV_CHAR);
				break;
			case KEY_RIGHT:
				/* Go to previous field */
				break;
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
				form_driver(my_form, ch);
				break;
		}
	}

	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]); 

	endwin();
	return 0;
}