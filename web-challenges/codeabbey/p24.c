#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_NUMS 1024

enum bool {FALSE, TRUE};

/* calculate_pseudorandom: calculate a pseudorandom number using Neumann's
 * random number generator */
unsigned long int calculate_pseudorandom(unsigned long int seed) {
	seed *= seed;
	seed /= 100;
	seed %= 10000;
	return seed;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t i, n_tests;
	/* get first string, which contains the number of test cases */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	/* get second string, which contains the seeds */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	for (i = 0; i < n_tests; i++) {
		/* declare/initialize variables */
		unsigned long int random[MAX_NUMS];
		size_t j, iterations = 0;
		char match = FALSE;
		/* the original seed will always be in positions 0 */
		random[0] = strtoul(input_position, &input_position, 10);
		/* iterate through the random numbers until MAX_NUMS is reached or a
		 * repeat occurs */
		for (j = 1; j < MAX_NUMS && match == FALSE; j++) {
			/* initialize variable k */
			size_t k = j;
			/* calculate the new random number from the last one */
			random[j] = calculate_pseudorandom(random[j - 1]);
			/* loop through all the previous randoms and see if any match the
			 * current one */
			while (k-- != 0) {
				if (random[k] == random[j]) {
					match = TRUE;
					iterations = j;
					break;
				}
			}
		}
		/* it is an error if we reached the limit of the random array without a
		 * match */ 
		if (j == MAX_NUMS && match == FALSE) {
			fprintf(stderr, "error\n");
			exit(EXIT_FAILURE);
		}
		/* print results */
		printf((i == n_tests - 1) ? "%lu\n" : "%lu ", iterations);
	}
	return 0;
}
