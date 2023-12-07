#include "contact.h"

struct Contact {
	char name[255];
	char phone_number[15];
	char email[320];
};

typedef struct Contact Contact;

// Contact* new_contact(char* name, char* phone_number, char* email) {
// 	Contact* new_contact = malloc(sizeof(Contact));

// 	new_contact->name = strdup(name);
// 	new_contact->phone_number = strdup(phone_number);
// 	new_contact->email = strdup(email);

// 	printf("%d", 	strlen(new_contact->name));
	
// 	return new_contact;
// }

void get_contacts(FILE* file) {
	Contact contact;
	// int file_size;
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
	// char total_contacts_str[11];
	// int total_contacts;
	// long file_size;
	// char* file_copy;

	// file = fopen("contact_data.dat", "rb");
	// fseek(file, 8 * sizeof(char), SEEK_SET);
	// fread(&total_contacts_str, sizeof(char), 1, file);

	// total_contacts = atoi(total_contacts_str);
	// total_contacts += 1;
	// sprintf(total_contacts_str, "%d", total_contacts);
	// printf("%c", total_contacts_str[0]);

	// fseek(file, 0, SEEK_END);
	// file_size = ftell(file);
	// rewind(file);

	// file_copy = malloc(file_size + 1);
	// fread(file_copy, file_size, 1, file);

	// file_copy[file_size] = 0;
	// file_copy[8] = total_contacts_str[0];
	
	// file = fopen("contact_data.dat", "wb");
	// fwrite(file_copy, file_size, 1, file);

	// rewind(file);

	file = fopen("contact_data.dat", "ab+");
	if (file == NULL) {
		printf("ERROR!");
		exit(1);
	}

	fwrite(&new_contact, sizeof(Contact), 1, file);

	fclose(file);
}

void find_contact(char* search_term, FILE* file) {
	
}