/* Since girls have 2 legs and pigs have 4, our first equation is
 * 2*girls + 4*pigs = legs. Our second governing equation is
 * 2*girls + bpp*pigs = breasts. Combining these (and treating breasts and legs
 * as similar units), we can find:
 * pigs = (breasts - legs)/(bpp - 4), and the first equation can be rearranged
 * to yield girls = (legs - 4*pigs)/LEGS_PER_GIRL. */
#include <stdio.h>
#include <stdlib.h>
#define BREASTS_PER_GIRL 2
#define LEGS_PER_GIRL 2
#define LEGS_PER_PIG 4

int main(void) {
	unsigned int cases, i;
	unsigned int *feasible;
	/* get the number of cases */
	if (1 != scanf("%u\n", &cases)) {
		fprintf(stderr, "error reading input on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* an array to hold the number of feasible cases */
	feasible = calloc(cases, sizeof *feasible);
	for (i = 0; i < cases; i++) {
		int girls, pigs, legs, breasts, bpp;
		/* get the number of legs and breasts */
		if (2 != scanf("%d %d\n", &legs, &breasts)) {
			fprintf(stderr, "error reading input on line %u\n", i + 2);
			exit(EXIT_FAILURE);
		}
		/* initial value of bpp takes advantage of the given fact that
		 * legs < breasts; which implicitly means a > LEGS_PER_PIG because
		 * girls have equal numbers of legs and breasts */
		bpp = (0 == LEGS_PER_PIG%2) ? LEGS_PER_PIG + 2 : LEGS_PER_PIG + 1;
		/* compute the initial number of pigs and girls */
		pigs = (breasts - legs)/(bpp - LEGS_PER_PIG);
		girls = (legs - LEGS_PER_PIG*pigs)/LEGS_PER_GIRL;
		/* exclude negative numbers of girls and pigs, which are impossible */
		while (girls <= 0 || pigs <= 0) {
			bpp += 2;
			pigs = (breasts - legs)/(bpp - LEGS_PER_PIG);
			girls = (legs - LEGS_PER_PIG*pigs)/LEGS_PER_GIRL;
		}
		/* end condition is when girls and pigs are both 0 (integer division
		 * makes this apply to any result between 0 and 1) */
		while (0 != girls && 0 != pigs) {
			/* make sure the number of girls and pigs and value for bpp
			 * satisfy the original equations (because of division, a
			 * fractional part may have been truncated; we want to avoid
			 * this) */
			if (LEGS_PER_GIRL*girls + LEGS_PER_PIG*pigs == legs
					&& BREASTS_PER_GIRL*girls + bpp*pigs == breasts) {
				/*printf("g: %d, p: %d, l: %d, b: %d, bpp: %d\n", girls,
						pigs, legs, breasts, bpp);*/
				/* this answer is feasible */
				feasible[i]++;
			}
			/* assume pig breasts come in pairs, so += 2 */
			bpp += 2;
			/* calculate the next number of girls and pigs */
			pigs = (breasts - legs)/(bpp - LEGS_PER_PIG);
			girls = (legs - LEGS_PER_PIG*pigs)/LEGS_PER_GIRL;
		}
	}
	/* print the results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%u\n" : "%u ", feasible[i]);
	}
	/* clean up */
	free(feasible);
	return 0;
}
