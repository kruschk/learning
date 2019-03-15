#include <stdio.h>
#include <ctype.h>
#include <string.h>

int strrcmp(char *s, char *t);
int print_characters(int (*character_converter)(int));

int main(int argc, char *argv[]) {
	if (argc > 1) {
		printf("usage: %s [<input_file]\n", argv[0]);
		return -1;
	}
	else if (strrcmp(argv[0], "lower") == 0) {
		print_characters(tolower);
		return 0;
	}
	else if (strrcmp(argv[0], "upper") == 0) {
		print_characters(toupper);
		return 0;
	}
	return -1;
}

/* strrcmp: compare string s and t from the right, return 0 if t matches the
 * end of string s */
int strrcmp(char *s, char *t) {
	size_t i = strlen(s) - 1;
	size_t j = strlen(t) - 1;
	while (s[i] == t[j] && i != 0 && j != 0) {
		i--;
		j--;
	}
	if (s[i] == t[j] && j == 0) {
		return 0;
	}
	return 1;
}

/* print_characters: print the characters from STDIN according to
 * character_converter */
int print_characters(int (*character_converter)(int)) {
	int c;
	while ((c = getchar()) != EOF) {
		putchar((*character_converter)(c));
	}
	return 0;
}
