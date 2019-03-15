#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

/* find_triple: find the set of triples that satisfy a^2 + b^2 = c^2 and
 * a + b + c = sum simultaneously and store the answers in a, b, and c*/
unsigned int find_triple(unsigned long int sum, unsigned long int *a,
		unsigned long int *b, unsigned long int *c) {
	/* i corresponds with a */
	unsigned long int i;
	for (i = 1; i < sum; i++) {
		/* if this division gives us an integer */
		if ((sum*sum-2*sum*i)%(2*sum-2*i) == 0) {
			/* only assign variables if we weren't passed NULL pointers */
			if (a != NULL) {
				*a = i;
			}
			if (b != NULL) {
				*b = (sum*sum-2*sum*i)/(2*sum-2*i);
			}
			if (c != NULL) {
				*c = sum - i - *b;
			}
			/* return the value of c to signal success */
			return *c;
		}
	}
	/* 0 signals failure */
	return 0;
}

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get the number of test cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* compute c*c for each case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		unsigned long int a, b, c, sum;
		/* get the sum */
		fgets(line, MAX_LINE, stdin);
		sum = strtoul(line, NULL, 10);
		/* determine the sum */
		if (find_triple(sum, &a, &b, &c) > 0) {
			/* if we want to know what a, b, and c are */
			/*printf("%lu %lu %lu ", a, b, c);*/
			/* print result */
			printf((i == n_cases - 1) ? "%lu\n" : "%lu ", c*c);
		}
	}
	return 0;
}
