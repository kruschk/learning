#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	char *input_position;
	size_t i, number_of_tests;
	unsigned long a, b, c, intermediate, sum;
	/* get the first number and convert it to long */
	fgets(input, MAX_LINE, stdin);
	number_of_tests = strtoul(input, NULL, 10);
	/* calculate the sum of digits from the intermediate on each line */
	for (i = 0; i < number_of_tests; i++) {
		sum = 0;
		/* gather input */
		fgets(input, MAX_LINE, stdin);
		a = strtoul(input, &input_position, 10);
		b = strtoul(input_position, &input_position, 10);
		c = strtoul(input_position, NULL, 10);
		/* compute the intermediate */
		intermediate = a*b + c;
		/* sum each digit in the intermediate */
		while (intermediate != 0) {
			sum += intermediate % 10;
			intermediate /= 10;
		}
		/* format printing so there's no trailing space */
		(i == number_of_tests-1) ? printf("%lu\n", sum) : printf("%lu ", sum);
	}
	return 0;
}
