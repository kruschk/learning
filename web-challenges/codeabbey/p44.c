#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define N_SIDES 6
#define LOW 1

/* scale_shift_random: scales a random integer in the range [0, UINT_MAX] to
 * [shift, distinct_values]. I.e. for a 6-sided die, we want the range of
 * values to be [1, 6], so we call scale_shift_random(random_num, 6, 1). */
unsigned int scale_shift_random(unsigned int num, unsigned int distinct_values,
		unsigned int shift) {
	return num % distinct_values + shift;
}

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get number of test cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* calculate the sum of the two throws for each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare/initialize variables */
		char *line_p;
		unsigned int a, b, result;
		/* get the random numbers */
		fgets(line, MAX_LINE, stdin);
		a = strtoul(line, &line_p, 10);
		b = strtoul(line_p, NULL, 10);
		/* calculate the sum of the two numbers */
		result = scale_shift_random(a, N_SIDES, LOW)
			+ scale_shift_random(b, N_SIDES, LOW);
		/* print result */
		printf((i == n_cases - 1) ? "%u\n" : "%u ", result);
	}
	return 0;
}
