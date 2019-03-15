#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

/* gcd: compute the greatest common divisor of two numbers a and b */
unsigned long gcd(unsigned long a, unsigned long b) {
	while (a != b) {
		if (a < b) {
			b -= a;
		}
		else {
			a -= b;
		}
	}
	return a;
}

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
		unsigned long a, b, greatest_common_divisor, least_common_multiple;
		/* collect required parameters from the next line */
		fgets(input, MAX_LINE, stdin);
		a = strtoul(input, &input_position, 10);
		b = strtoul(input_position, &input_position, 10);
		/* compute the greatest common divisor */
		greatest_common_divisor = gcd(a, b);
		/* compute the least common multiple */
		least_common_multiple = a*b/greatest_common_divisor;
		/* print results */
		printf((i == n_tests - 1) ? "(%lu %lu)\n" : "(%lu %lu) ",
				greatest_common_divisor, least_common_multiple);
	}
	return 0;
}
