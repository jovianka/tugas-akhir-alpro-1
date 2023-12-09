#include <stdio.h>
#include "contact.h"


int main() {
	FILE* file;
	Contact contact;

	Contact example_contact = {"UNO", "15", "wahmen"};
	// add_contact(example_contact, file);
	// get_contacts(file);
	// delete_contact(1, file);
	// printf("\n");
	// get_contacts(file);

	get_contacts(file);
	printf("\n");
	unsigned long* searched_positions = search_contacts("cin", file);

	if (searched_positions[0] > 0) {
		printf("found %d matches\n", searched_positions[0]);
		for (int i = 1; i <= searched_positions[0]; i++) {
			printf("at %d\n", searched_positions[i]);
		}
	}

	return 0;
}