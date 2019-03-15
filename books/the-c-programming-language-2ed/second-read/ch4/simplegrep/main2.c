#include <stdio.h>
#include <stdlib.h>

int strindex(char source[], char searchfor[]);

/* find all lines matching pattern */
int main(void) {
	char pattern[] = "ould"; /* pattern to search for */
	int found = 0;
	size_t n = 10;
	char *line = malloc(n);

	while (getline(&line, &n, stdin) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}

	/*free(line);*/
	return found;
}
