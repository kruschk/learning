#include <gmp.h>
#include <stdio.h>

/* fibonacci: compute the nth fibonacci number and store the result in ans */
void fibonacci(unsigned int n, mpz_t ans) {
	/* declare/initialize gmp variables */
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
	return;
}

int main(void) {
	unsigned int cases, i;
	/* get the number of cases */
	scanf("%u\n", &cases);
	/* determine the index for each case */
	for (i = 0; i < cases; i++) {
		/* declare/initialize variables */
		unsigned int divisor, j;
		mpz_t fib;
		mpz_init(fib);
		/* get the divisor */
		scanf("%u", &divisor);
		/* find the index of the fibonacci number that is evenly divisible by
		 * divisor */
		j = 1;
		for (fibonacci(j, fib); mpz_tdiv_ui(fib, divisor) != 0; j++) {
			fibonacci(j, fib);
		}
		j--;
		/* clear memory */
		mpz_clear(fib);
		/* print the result */
		printf((i == cases - 1) ? "%u\n" : "%u ", j);
	}
	return 0;
}
