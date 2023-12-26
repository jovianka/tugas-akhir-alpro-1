#include "utils.h"


char* str_tolower(const char* str) {
  char* lowercased_string = (char*) malloc(strlen(str) * sizeof(char) + sizeof(char));
  for (int i = 0; i < strlen(str); i++) {
    lowercased_string[i] = tolower(str[i]);
  }
  lowercased_string[strlen(str)] = '\0';

  return lowercased_string;
}

char* trim_whitespaces(char* str) {
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}