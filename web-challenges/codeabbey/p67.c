#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_FIBONACCI 1000

/* fibonacci: compute the nth fibonacci number, then assign it to index n of
 * array */
void fibonacci(unsigned int n, mpz_t array[]) {
	/* declare/initialize gmp variables */
	mpz_t ans;
	mpz_init(ans);
	/* fibonacci(0) is 0 */
	if (n == 0) {
		mpz_set_ui(ans, 0);
	}
	/* fibonacci(1) is 1 */
	else if (n == 1) {
		mpz_set_ui(ans, 1);
	}
	/* fibonacci(n) is fibonacci(n-2) + fibonacci(n-1) */
	else {
		unsigned int i;
		/* declare/initialize gmp variables */
		mpz_t prevprev;
		mpz_t prev;
		mpz_init_set_ui(prevprev, 0);
		mpz_init_set_ui(prev, 1);
		/* compute the fibonacci number */
		for (i = 2; i <= n; i++) {
			mpz_add(ans, prevprev, prev);
			mpz_set(prevprev, prev);
			mpz_set(prev, ans);
		}
		/* free memory */
		mpz_clear(prevprev);
		mpz_clear(prev);
	}
	/* initialize the ith element of array and set it to ans */
	mpz_init_set(array[n], ans);
	/* clear the answer */
	mpz_clear(ans);
	return;
}

/* wrapper function to use bsearch with gmp bignums */
int mpz_cmp_wrapper(const void *keyval, const void *datum) {
	/* Cast keyval and datum to the type of fibonaccis (mpz_t *), then
	 * dereference. This is a general rule for bsearch and qsort, where
	 * fibonaccis is the base array */
	return mpz_cmp(*(mpz_t *)keyval, *(mpz_t *)datum);
}

int main(void) {
	unsigned int i, cases;
	mpz_t fibonaccis[MAX_FIBONACCI]; /* array of fibonacci numbers */
	mpz_t number; /* the desired fibonacci number */
	/* populate an array of the first MAX_FIBONACCI fibonacci numbers */
	for (i = 0; i < MAX_FIBONACCI; i++) {
		fibonacci(i, fibonaccis);
	}
	/* get the number of test cases and determine the index of the fibonacci
	 * number for each */
	scanf("%u\n", &cases);
	for (i = 0; i < cases; i++) {
		size_t index;
		mpz_t *location; /* points to the fibonacci number in fibonaccis */
		gmp_scanf("%Zd\n", number); /* get the number from stdin */
		/* search for the fibonacci number using bsearch */
		location = bsearch(&number, fibonaccis, MAX_FIBONACCI,
				sizeof *fibonaccis, mpz_cmp_wrapper);
		if (location != NULL) {
			/* compute the index from the returned location */
			index = location - fibonaccis;
			/* print the result */
			gmp_printf((i == cases - 1) ? "%lu\n" : "%lu ", index);
		}
	}
	/* clean up the gmp numbers */
	mpz_clear(number);
	for (i = 0; i < MAX_FIBONACCI; i++) {
		mpz_clear(fibonaccis[i]);
	}
	return 0;
}
