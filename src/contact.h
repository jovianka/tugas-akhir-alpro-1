#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

struct Contact;
typedef struct Contact Contact;

void get_contacts(FILE* file);
void add_contact(Contact new_contact, FILE* file);
void find_contact(char* search_term, FILE* file);