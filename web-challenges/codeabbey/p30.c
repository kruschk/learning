#include <stdio.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_ENTRIES 1024

int main(void) {
	/* declare variables */
	char input[MAX_LINE];
	size_t i, j;
	/* get string */
	fgets(input, MAX_LINE, stdin);
	/* discard trailing newline, if present */
	j = strlen(input) - 1;
	if (input[j] == '\n') {
		input[j] = '\0';
		j--;
	}
	/* reverse string in-place */
	for (i = 0; i < j; i++, j--) {
		char temp = input[i];
		input[i] = input[j];
		input[j] = temp;
	}
	/* print result */
	printf("%s\n", input);
	return 0;
}
