#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	char *input_position;
	size_t i, number_of_tests;
	unsigned long a_1, a_n, d, n, s_n, temp;
	/* get the first number and convert it to long */
	fgets(input, MAX_LINE, stdin);
	number_of_tests = strtoul(input, NULL, 10);
	/* apply the formula to each number */
	for (i = 0; i < number_of_tests; i++) {
		/* gather input */
		fgets(input, MAX_LINE, stdin);
		a_1 = strtoul(input, &input_position, 10);
		d = strtoul(input_position, &input_position, 10);
		n = strtoul(input_position, NULL, 10);
		/* apply the arithmetic sequence formula to determine the sum */
		a_n = a_1 + (n - 1)*d;
		temp = n*(a_1 + a_n);
		s_n = temp/2;
		s_n += temp%2; /* round by adding 0 or 1 depending on remainder */
		/* format printing so there's no trailing space */
		(i != number_of_tests - 1) ? printf("%ld ", s_n) :
			printf("%ld\n", s_n);
	}
	return 0;
}
