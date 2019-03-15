#include <stdio.h>

int any(const char str[], const char contains[]);
int check_for_match(const char c, const char str[]);

int main(void) {
	char str[] = "Hello there. This is a string which may make you slightly "
		"uncomfortable. Do not fret, however, because it is a perfectly "
		"acceptable string literal, according to the standard.\n";
	char contained_chars[] = "x";
	int position = any(str, contained_chars);

	printf("Position: %d\nProof: %c\n", position, str[position]);

	return 0;
}

/******************************************************************************
 * any: returns the first location in str where any character from the string
 * contains occurs, or -1 if there is no such location.
 *****************************************************************************/
int any(const char str[], const char contains[]) {
	int i;

	for (i = 0; str[i] != '\0'; ++i) {
		if (check_for_match(str[i], contains) == 1) {
			return i;
		}
	}

	return -1;
}

/******************************************************************************
 * check_for_match: check if the character c occurs in the string str.
 *****************************************************************************/
int check_for_match(const char c, const char str[]) {
	int i;
	for (i = 0; str[i] != 0; ++i) {
		if (c == str[i]) {
			return 1;
		}
	}

	return 0;
}
