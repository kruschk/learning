#include <stdio.h>

#define MAX_LINE 1024 /* maximum input line length */

int getline2(char line[], int max);
int strindex(char source[], char searchfor[]);


/* find all lines matching pattern */
int main(void) {
	char line[MAX_LINE];
	char pattern[] = "ould"; /* pattern to search for */
	int found = 0;

	while (getline2(line, MAX_LINE) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	return found;
}
