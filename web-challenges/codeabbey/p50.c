#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get the number of cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		size_t line_length, j, k;
		char stripped_line[MAX_LINE], answer;
		/* get the next line, which contains the string to test */
		fgets(line, MAX_LINE, stdin);
		/* remove all whitespace and punctuation and put the remaining
		 * characters in a new array */
		line_length = strlen(line);
		for (j = 0, k = 0; j < line_length; j++, k++) {
			/* skip whitespace and punctuation */
			while ((isspace(line[j]) || ispunct(line[j])) && j < line_length) {
				j++;
			}
			/* assign all other chars to stripped_line */
			stripped_line[k] = tolower(line[j]);
		}
		/* k now equals the length of stripped_line */
		stripped_line[--k] = '\0';
		k--;
		/* assume it's a palindrome */
		answer = 'Y';
		/* check if it's a palindrome */
		for (j = 0; j < k; j++, k--) {
			/* if we detect that it's not, set answer to 'N' and break */
			if (stripped_line[j] != stripped_line[k]) {
				answer = 'N';
				break;
			}
		}
		/* print result */
		printf((i == n_cases - 1) ? "%c\n" : "%c ", answer);
	}
	return 0;
}
