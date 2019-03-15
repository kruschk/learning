#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

enum bool {FALSE, TRUE};

/* is_vowel: returns TRUE if given character is a vowel, FALSE otherwise */
int is_vowel(char c) {
	switch (tolower(c)) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		case 'y':
			return TRUE;
			break;
		default:
			return FALSE;
			break;
	}
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE];
	size_t n_tests, i, j, vowel_count;
	/* determine number of test cases: */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	/* loop through each test case */
	for (i = 0; i < n_tests; i++) {
		/* gather next line into input */
		fgets(input, MAX_LINE, stdin);
		/* count vowels */
		vowel_count = 0; 
		for (j = 0; input[j] != '\0'; j++) {
			vowel_count += is_vowel(input[j]);
		}
		printf((i == n_tests - 1) ? "%lu\n" : "%lu ", vowel_count);
	}
	return 0;
}
