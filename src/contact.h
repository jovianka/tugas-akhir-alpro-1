#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <menu.h>
#include <panel.h>
#include <form.h>
#include "utils.h"

struct Contact {
	char name[256];
	char phone_number[16];
	char email[321];
	char address[256];
	char website[256];
	char birthday[32];
};

typedef struct Contact Contact;

void add_contact(Contact new_contact);
int modify_contact(int contact_index, Contact new_contact);
int delete_contact(int contact_index);
int get_search_count(const char* search_term);
int* search_and_get_contact_indices(const char* search_term);
Contact* search_and_get_contacts(const char* search_term);