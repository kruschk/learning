#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	char *input_position;
	size_t i, number_of_tests;
	unsigned long a, b, c, res;
	/* get the first number and convert it to long */
	fgets(input, MAX_LINE, stdin);
	number_of_tests = strtoul(input, NULL, 10);
	/* test each line to see if it describes a valid triangle */
	for (i = 0; i < number_of_tests; i++) {
		/* gather input */
		fgets(input, MAX_LINE, stdin);
		a = strtoul(input, &input_position, 10);
		b = strtoul(input_position, &input_position, 10);
		c = strtoul(input_position, NULL, 10);
		/* test the lengths using the triangle inequality theorem */
		if ((a + b > c) && (a + c > b) && (b + c > a)) {
			res = 1;
		}
		else {
			res = 0;
		}
		/* format printing so there's no trailing space */
		(i != number_of_tests - 1) ? printf("%ld ", res) :
			printf("%ld\n", res);
	}
	return 0;
}
