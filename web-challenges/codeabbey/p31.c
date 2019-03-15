#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

/* swap entries of type "type" in array "array" at positions i and j */
#define SWAP(type, array, i, j)\
	type temp = array[i];\
	array[i] = array[j];\
	array[j] = temp

/* rotate_string: rotate string in-place left or right, bytewise */
void rotate_string(int k, char *str) {
	size_t last_pos = strlen(str) - 1;
	/* if k is positive, rotate left, since k will end up at 0, next while loop
	 * won't be performed */
	while (k > 0) {
		size_t i;
		for (i = 0; i < last_pos; i++) {
			SWAP(char, str, i, i + 1);
		}
		k--;
	}
	/* if k is negative, rotate right */
	while (k < 0) {
		size_t i;
		for (i = last_pos; i > 0; i--) {
			SWAP(char, str, i - 1, i);
		}
		k++;
	}
	return;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE];
	size_t n_cases, i;
	/* get number of test cases from first line */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* perform string rotation on each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		int k;
		char *input_position;
		/* collect next string */
		fgets(input, MAX_LINE, stdin);
		k = strtol(input, &input_position, 10);
		/* skip the space so input position points to string to be rotated */
		input_position++;
		/* remove trailing newline */
		if (input_position[strlen(input_position) - 1] == '\n') {
			input_position[strlen(input_position) - 1] = '\0';
		}
		/* rotate the string */
		rotate_string(k, input_position);
		/* print results */
		printf((i == n_cases - 1) ? "%s\n" : "%s ", input_position);
	}
	return 0;
}
