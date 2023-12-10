#include "contact.h"


void get_contacts(FILE* file) {
	Contact contact;
	int total_contacts = 1;

	file = fopen("contact_data.dat", "rb");
	if (file == NULL) {
		printf("ERROR!");
		exit(1);
	}

	while (fread(&contact, sizeof(Contact), 1, file)) {
		printf("%d: %s, %s, %s\n", total_contacts, contact.name, contact.phone_number, contact.email);
		total_contacts++;
	}

	fclose(file);
}


void add_contact(Contact new_contact, FILE* file) {
	file = fopen("contact_data.dat", "ab+");
	if (file == NULL) {
		printf("ERROR OPENING FILE (FILE NOT FOUND)");
		exit(1);
	}

	fwrite(&new_contact, sizeof(Contact), 1, file);

	fclose(file);
}


void delete_contact(long contact_index, FILE* file) {
	// IMPORTANT: contact_index starts from 1
	long file_size;
	Contact* new_contacts;
	Contact contact_copy;
	contact_index *= sizeof(Contact);
	int i = 0;

	file = fopen("contact_data.dat", "rb");

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	new_contacts =  malloc(file_size - sizeof(Contact));

	while (fread(&contact_copy, sizeof(Contact), 1, file)) {
		if (ftell(file) == contact_index) {
			continue;
		}

		new_contacts[i] = contact_copy;
		i++;
	}

	file = fopen("contact_data.dat", "wb");
	fwrite(new_contacts, file_size - sizeof(Contact), 1, file);

	fclose(file);

	free(new_contacts);
}

int* search_contacts(const char* search_term, FILE* file) {
	file = fopen("contact_data.dat", "rb");
	Contact current_contact;
	char* lowercased_search_term = str_tolower(search_term);
	int* searched_positions = (int*) malloc(sizeof(int));
	int found_count = 0;
	searched_positions[0] = found_count;
	
	rewind(file);

	while (fread(&current_contact, sizeof(Contact), 1, file)) {
		char* lowercased_contact_name = str_tolower(current_contact.name);
		char* lowercased_contact_phone_number = str_tolower(current_contact.phone_number);
		char* lowercased_contact_email = str_tolower(current_contact.email);

		if (strstr(lowercased_contact_name, lowercased_search_term) != NULL || strstr(lowercased_contact_phone_number, lowercased_search_term) != NULL || strstr(lowercased_contact_email, lowercased_search_term) != NULL) {
			found_count++;
			searched_positions = realloc(searched_positions, (found_count + 1) * sizeof(int));
			searched_positions[found_count] = ftell(file) / sizeof(Contact) ;
			
			searched_positions[0] = found_count;
		}
		free(lowercased_contact_name);
		free(lowercased_contact_phone_number);
		free(lowercased_contact_email);

	}
	free(lowercased_search_term);

	fclose(file);
	return searched_positions;

}