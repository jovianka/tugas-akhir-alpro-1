#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include "utils.h"

struct Contact {
	char name[255];
	char phone_number[15];
	char email[320];
};

typedef struct Contact Contact;

void get_contacts(FILE* file);
void add_contact(Contact new_contact, FILE* file);
void delete_contact(long contact_index, FILE* file);
unsigned long* search_contacts(const char* search_term, FILE* file);