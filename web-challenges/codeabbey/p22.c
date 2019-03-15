#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_NUM 20

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_tests, i;
	unsigned long x, y, n, t, result;
	/* determine number of values and max number: */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, &input_position, 10);
	/* loop through each test case */
	for (i = 0; i < n_tests; i++) {
		/* gather next line into input */
		fgets(input, MAX_LINE, stdin);
		/* get required values */
		x = strtoul(input, &input_position, 10);
		y = strtoul(input_position, &input_position, 10);
		n = strtoul(input_position, NULL, 10);
		/* Use t as a clock, and determine whether the printers have printed
		 * the required number of documents on each iteration. */
		result = 0;
		t = 0;
		while (result < n) {
			t++;
			/* fractional parts are discarded due to integer division, which is
			 * key to this method */
			result = t/x + t/y;
		}
		/* print results */
		printf((i == n_tests - 1) ? "%lu\n" : "%lu ", t);
	}
	return 0;
}
