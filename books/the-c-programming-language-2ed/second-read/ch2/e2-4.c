#include <stdio.h>

int squeeze_string(char str[], const char chars_to_remove[]);
int check_for_match(const char c, const char str[]);

int main(void) {
	char to_be_squeezed[] = "Hello there. This is a string which may make "
		"you slightly uncomfortable. Do not fret, however, because it is a "
		"perfectly acceptable string literal, according to the standard.\n";
	
	char remove_chars[] = "abcd";

	squeeze_string(to_be_squeezed, remove_chars);

	printf("%s", to_be_squeezed);

	return 0;
}

int squeeze_string(char str[], const char chars_to_remove[]) {
	int i, j;

	for (i = j = 0; str[i] != '\0'; ++i) {
		if (check_for_match(str[i], chars_to_remove) == 0) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';

	return 0;
}

/* check if the character c occurs in the string str */
int check_for_match(const char c, const char str[]) {
	int i;
	for (i = 0; str[i] != 0; ++i) {
		if (c == str[i]) {
			return 1;
		}
	}

	return 0;
}
