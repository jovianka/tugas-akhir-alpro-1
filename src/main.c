#include <stdio.h>
#include "contact.h"


int main() {
	FILE* file;
	Contact contact;

	// Contact example_contact = {"quatro cinco", "15", "wahmen"};
	// add_contact(example_contact, file);
	get_contacts(file);
	delete_contact(1, file);
	printf("\n");
	get_contacts(file);

	return 0;
}