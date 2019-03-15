#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

static double a, b, c, d;

/* monotonic_function: returns the value of
 * f(x) = a*x + b*sqrt(x^3) - c*e^(-x/50.0) - d */
static double monotonic_function(double x) {
	return a*x + b*sqrt(pow(x, 3)) - c*exp(-x/50.0) - d;
}

/* binary_search: uses the binary search algorithm to find the root of the
 * passed objective function */
static double binary_search(double (*objective_function)(double), double low,
		double high) {
	double mid = (low + high)/2.0; /* x-value halfway between low and high */
	double epsilon = (1.0e-7)/2.0; /* acceptable error is +/- epsilon */
	/* implement binary search */
	double result = objective_function(mid); 
	while ((result < -epsilon || result > epsilon)) {
		if (result < -epsilon) {
			low = mid;
		}
		else {
			high = mid;
		}
		mid = (low + high)/2.0;
		result = objective_function(mid);
	}
	/* return the root */
	return mid;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_cases, i;
	/* get the number of cases from the first line */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* find the root for each case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		double root;
		/* get required parameters */
		fgets(input, MAX_LINE, stdin);
		a = strtod(input, &input_position);
		b = strtod(input_position, &input_position);
		c = strtod(input_position, &input_position);
		d = strtod(input_position, NULL);
		/* calculate the root */
		root = binary_search(monotonic_function, 0, 100);
		/* print result */
		printf((i == n_cases - 1) ? "%.8f \n" : "%.8f ", root);
	}
	return 0;
}
