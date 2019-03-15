#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char input[MAX_LINE];
	size_t n_tests, i;
	/* get first string, which contains the number of test cases */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	for (i = 0; i < n_tests; i++) {
		/* declare variables */
		char *input_position;
		size_t j;
		unsigned long a, c, m, x_j_minus_1, n, x_j;
		/* collect required parameters from the next line */
		fgets(input, MAX_LINE, stdin);
		a = strtoul(input, &input_position, 10);
		c = strtoul(input_position, &input_position, 10);
		m = strtoul(input_position, &input_position, 10);
		x_j_minus_1 = strtoul(input_position, &input_position, 10);
		n = strtoul(input_position, NULL, 10);
		/* calculate the nth value of the random number generator with the
		 * given values */
		for (j = 1; j <= n; j++) {
			x_j = (a*x_j_minus_1 + c) % m;
			x_j_minus_1 = x_j;
		}
		/* print results */
		printf((i == n_tests - 1) ? "%lu\n" : "%lu ", x_j);
	}
	return 0;
}
