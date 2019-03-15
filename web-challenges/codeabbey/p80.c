#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"

int main(void) {
	unsigned short int cases, i;
	/* get the number of cases */
	if (1 != scanf("%hu\n", &cases)) {
		fprintf(stderr, "error getting the number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < cases; i++) {
		double pA, pB, pA_wins;
		/* get the probability that Alan kills Bob and the probability that Bob
		 * kills Alan on their respective turns */
		if (2 != scanf("%lf %lf\n", &pA, &pB)) {
			fprintf(stderr, "error getting the number of cases on line 1\n");
			exit(EXIT_FAILURE);
		}
		/* convert from percent to fraction */
		pA /= 100.0;
		pB /= 100.0;
		/* compute the probability that A wins in any round */
		pA_wins = pA/(1.0-(1.0-pA)*(1.0-pB));
		/* print the result */
		printf((i == cases - 1) ? "%lu\n" : "%lu ", custom_round(pA_wins*100.0));
	}
	return 0;
}
