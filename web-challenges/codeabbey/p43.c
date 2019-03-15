#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define N_SIDES 6
#define LOW 1

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get number of test cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* calculate an int for each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare/initialize variables */
		double random;
		int result;
		/* get the next random number */
		fgets(line, MAX_LINE, stdin);
		random = strtod(line, NULL);
		/* since result is an integer, fractional part will be discarded */
		result = N_SIDES*random + LOW;
		/* print result */
		printf((i == n_cases - 1) ? "%d\n" : "%d ", result);
	}
	return 0;
}
