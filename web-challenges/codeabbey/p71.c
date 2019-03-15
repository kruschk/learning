#include <stdio.h>
#include <stdlib.h>

int main(void) {
	unsigned int i, cases;
	int scan_status = 0;
	/* get number of cases */
	scan_status = scanf("%u\n", &cases);
	if (scan_status != 1) {
		fprintf(stderr, "failed to get number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* for each case, determine the index of the first fibonacci number that is
	 * evenly divisible by divisor */
	for (i = 0; i < cases; i++) {
		unsigned int divisor, j, ans;
		unsigned int prevprev = 0;
		unsigned int prev = 1;
		/* get the divisor */
		scan_status = scanf("%u", &divisor);
		if (scan_status != 1) {
			fprintf(stderr, "input read error on input number %u\n", i + 1);
			exit(EXIT_FAILURE);
		}
		/* find the index */
		j = 1;
		do {
			j++;
			ans = (prevprev + prev)%divisor;
			prevprev = prev;
			prev = ans;
		}
		while (ans != 0);
		/* print the result */
		printf((i == cases - 1) ? "%u\n" : "%u ", j);
	}
	return 0;
}
