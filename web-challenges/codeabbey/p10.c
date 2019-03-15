#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"
#define MAX_LINE 1024

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	char *input_position;
	size_t i, number_of_tests;
	long x_1, y_1, x_2, y_2;
	double m, b;
	/* get the first number and convert it to long */
	fgets(input, MAX_LINE, stdin);
	number_of_tests = strtoul(input, NULL, 10);
	/* determine the slope and intercept of the line on which the two points
	 * lie */
	for (i = 0; i < number_of_tests; i++) {
		/* gather input */
		fgets(input, MAX_LINE, stdin);
		x_1 = strtoul(input, &input_position, 10);
		y_1 = strtoul(input_position, &input_position, 10);
		x_2 = strtoul(input_position, &input_position, 10);
		y_2 = strtoul(input_position, NULL, 10);
		/* compute slope and intercept */
		m = (double)(y_2 - y_1)/(double)(x_2 - x_1);
		b = (double)y_1 - m*(double)x_1;
		/* format printing so there's no trailing space */
		(i != number_of_tests - 1) ?
			printf("(%ld %ld) ", custom_round(m), custom_round(b)) :
			printf("(%ld %ld)\n", custom_round(m), custom_round(b));
	}
	return 0;
}
