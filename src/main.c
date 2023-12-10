#include <stdio.h>
#include "contact.h"


int main() {
	FILE* file;
	Contact contact;

	Contact example_contact = {"NEW DOS", "15", "zz"};
	// add_contact(example_contact, file);
	// get_contacts(file);
	// delete_contact(1, file);
	// printf("\n");
	// get_contacts(file);

	// get_contacts(file);
	// printf("\n");
	// int* searched_positions = search_contacts("UNO", file);

	// if (searched_positions[0] > 0) {
	// 	printf("found %d match(es)\n", searched_positions[0]);
	// 	for (int i = 1; i <= searched_positions[0]; i++) {
	// 		printf("at index %d\n", searched_positions[i]);
	// 	}
	// }

	// free(searched_positions);

	get_contacts(file);
	modify_contact(2, example_contact, file);
	printf("\n");
	get_contacts(file);

	return 0;
}