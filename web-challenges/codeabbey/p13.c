#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	char *input_position;
	size_t i, number_of_tests, count;
	unsigned long sum;
	/* get the first number and convert it to long */
	fgets(input, MAX_LINE, stdin);
	number_of_tests = strtoul(input, NULL, 10);
	/* get the second line, which contains all the input numbers */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* calculate weighted sum of digits for each line */
	for (i = 0; i < number_of_tests; i++) {
		/* skip whitespace */
		while (isspace(*input_position)) {
			input_position++;
		}
		/* calculate weighted sum from string */
		sum = 0;
		count = 1;
		while (!isspace(*input_position) && *input_position != '\0') {
			sum += count*(*input_position - '0');
			input_position++;
			count++;
		}
		/* format printing so there's no trailing space */
		(i == number_of_tests-1) ? printf("%lu\n", sum) : printf("%lu ", sum);
	}
	return 0;
}
