#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 4096
#define MAX_NUMS 1024
#define MODULO 10000007
#define MULTIPLY 113

int main(void) {
	/* declare/initialize variables */
	size_t i, j, n, n_tests;
	char input[MAX_LINE], *input_position;
	double root;
	unsigned x;
	/* determine number of test cases from first line */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	for (i = 0; i < n_tests; i++) {
		/* get the specified values from the next line */
		fgets(input, MAX_LINE, stdin);
		x = strtoul(input, &input_position, 10);
		n = strtoul(input_position, NULL, 10);
		/* use Heron's formula to approximate r */
		for (root = 1, j = 0; j < n; j++) {
			root = (root + (double)x/root)/2;
		}
		/* print results */
		(i == n_tests - 1) ? printf("%.10f\n", root) : printf("%.10f ", root);
	}
	return 0;
}
