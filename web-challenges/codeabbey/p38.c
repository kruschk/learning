#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"
#define MAX_LINE 1024

/* define a structure to hold the real and imaginary parts of a complex
 * number */
struct complex_num {
	int real;
	int imag;
};

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_cases, i;
	/* determine number of test cases */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* compute solutions for each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		int a, b, c, radicand;
		struct complex_num x_1, x_2;
		/* get quadratic equation parameters a, b, and c */
		fgets(input, MAX_LINE, stdin);
		a = strtol(input, &input_position, 10);
		b = strtol(input_position, &input_position, 10);
		c = strtol(input_position, NULL, 10);
		/* calculate the radicand */
		radicand = b*b-4*a*c;
		/* if it's nonnegative, it will only have a real part: */
		if (radicand >= 0) {
			/* compute x_1 */
			x_1.real = custom_round((-b + sqrt(radicand))/(2.0*a));
			/* compute x_2 */
			x_2.real = custom_round((-b - sqrt(radicand))/(2.0*a));
			/* print results */
			printf((i == n_cases - 1) ? "%d %d\n" : "%d %d; ", x_1.real,
					x_2.real);
		}
		/* otherwise, it will have a real and imaginary part */
		else {
			/* compute both parts of x_1 */
			x_1.real = custom_round(-b/(2.0*a));
			x_1.imag = custom_round(sqrt(-radicand)/(2.0*a));
			/* compute both parts of x_2 */
			x_2.real = custom_round(-b/(2.0*a));
			x_2.imag = custom_round(-sqrt(-radicand)/(2.0*a));
			/* print results */
			printf((i == n_cases - 1) ? "%d%+di %d%+di\n" : "%d%+di %d%+di; ",
					x_1.real, x_1.imag, x_2.real, x_2.imag);
		}
	}
	return 0;
}
