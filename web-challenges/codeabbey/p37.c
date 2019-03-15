/* CodeAbbey problem 37: Mortgage Calculator
 * The principal p at month n can be calculated as follows:
 * p_(n+1) =  p_n + p_n*r/(12*100) - m = p_n*(1 + r/(12*100)) - m = c*p_n - m
 * p_1 = c*p_0 - m
 * p_2 = c*p_1 - m = c*(c*p_0 - m) - m = c^2*p_0 - c*m - m
 * p_3 = c*p_2 - m = c*(c^2*p_0 - c*m - m) - m = c^3*p_0 - c^2*m - c*m - m
 * ...
 * p_n = c^n*p_0 - m*(c^(n-1) + c^(n-2) + ... + c^1 + c^0)
 * Therefore:
 * m = (c^n*p_0 - p_n)/(c^(n-1) + c^(n-2) + ... + c^1 + c^0) */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

/* monthly_payments: computes the monthly payments required to reduce the
 * principal from start_principal to the end_principal in months time.
 * annual_interest is an annual interest rate, in percent. */
double monthly_payments(double annual_interest, double start_principal,
		double end_principal, double months) {
	double c = 1.0 + annual_interest/(12.0*100.0);
	/* compute the numerator (see expression for m above) */
	double numerator = pow(c, months)*start_principal - end_principal;
	/* compute denominator (see m again) */
	size_t i;
	double denominator = 0.0;
	for (i = 0; i < months; i++) {
		denominator += pow(c, i);
	}
	/* return the ratio, which is m */
	return numerator/denominator;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	double p_0, r, n, p_n;
	unsigned int m;
	/* gather input parameters */
	fgets(input, MAX_LINE, stdin);
	p_0 = strtod(input, &input_position);
	r = strtod(input_position, &input_position);
	n = strtod(input_position, NULL);
	/* we want the principal to be zero at the end, so set p_n = 0; */
	p_n = 0;
	/* compute the required monthly payments to completely pay off the mortgage
	 * in n months, rounded up to the nearest dollar */
	m = ceil(monthly_payments(r, p_0, p_n, n));
	/* print result */
	printf("%u\n", m);
	return 0;
}
