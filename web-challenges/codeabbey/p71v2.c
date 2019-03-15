/* Uses the algorithm described by user Mark Bennett at
 * https://math.stackexchange.com/questions/1147447/how-to-find-a-fibonacci-number-that-is-divisible-by-x */

#include <stdio.h>
#include <stdlib.h>
#include "gen-primes.h"
#define MAX_DIVISOR 2000000
/* MAX_NUM_FACTORS = floor(log2(MAX_DIVISOR)); a given number can have at most
 * log2(MAX_DIVISOR) primes:
 * https://www.quora.com/How-many-prime-factors-can-a-number-have-maximum */
#define MAX_NUM_FACTORS 20 
#define MAX_NUM_PRIMES 100000
#define MAX_PRIME 2000000

/* gcd: compute the greatest common divisor of two nonnegative integers using
 * Euclid's algorithm */
unsigned int gcd(unsigned int a, unsigned int b) {
	while (a != b) {
		if (a > b) {
			a -= b;
		}
		else {
			b -= a;
		}
	}
	return a;
}

/* lcm: compute the least common multiple of two nonnegative integers */
unsigned int lcm(unsigned int a, unsigned int b) {
	return a*b/gcd(a, b);
}

/* generate_prime_factors: generate the prime factors of a number */
enum boolean generate_prime_factors(unsigned int num, unsigned int factors[],
		size_t factors_length, size_t *used_length, unsigned int primes[],
		size_t primes_length) {
	size_t i = 0, j = 0;
	while (num > 1 && i < factors_length && j < primes_length) {
		if (num%primes[j] == 0) {
			factors[i] = primes[j];
			num /= primes[j];
			/* repeated primes are multiplied together */
			while (num%primes[j] == 0 && num > 1) {
				factors[i] *= primes[j];
				num /= primes[j];
			}
			i++; /* don't overwrite factors[i] */
		}
		else {
			j++; /* go to next prime */
		}
	}
	if (num == 1) {
		*used_length = i;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/* fib_n_mod_m: compute the remainder of the nth fibonacci number divided by
 * m */
unsigned int fib_n_mod_m(unsigned int n, unsigned int m) {
	if (m <= 0) {
		fprintf(stderr, "fib_n_mod_m: invalid divisor");
		exit(EXIT_FAILURE);
	}
	if (n == 0) {
		return 0; /* 0 mod anything > 0 is 0, so don't need %m */
	}
	else if (n == 1) {
		return 1%m; /* will be 0 or 1 */
	}
	else {
		unsigned int prevprev = 0;
		unsigned int prev = 1;
		unsigned int ans;
		unsigned int i;
		for (i = 2; i <= n; i++) {
			/* take advantage of modular arithmetic to prevent overflow */
			ans = (prevprev + prev)%m;
			prevprev = prev;
			prev = ans;
		}
		return ans;
	}
}

int main(void) {
	unsigned int i, cases;
	size_t primes_arr_len = MAX_NUM_PRIMES;
	size_t primes_used_len;
	unsigned int *primes = malloc(MAX_NUM_PRIMES*sizeof *primes);
	/* generate an array of primes */
	generate_prime_array(&primes, &primes_arr_len, &primes_used_len, MAX_PRIME);
	scanf("%u\n", &cases);
	/* determine the index of the first fibonacci number divisible by the
	 * input divisor for each case */
	for (i = 0; i < cases; i++) {
		unsigned int divisor, j, k;
		unsigned int factors[MAX_NUM_FACTORS];
		unsigned int indeces[MAX_NUM_FACTORS];
		unsigned int common_lcm = 1;
		size_t factors_used_len = 0;
		scanf("%u", &divisor);
		/* generate an array containing the prime factors of the divisor */
		generate_prime_factors(divisor, factors, MAX_NUM_FACTORS,
				&factors_used_len, primes, primes_used_len);
		/* get the index of the fibonacci number associated with each prime
		 * factor */
		for (j = 0, k = 1; j < factors_used_len; j++) {
			/* factors are in ascending order, so don't need to reset k to 1 */
			while (fib_n_mod_m(k, factors[j]) != 0) {
				k++;
			}
			indeces[j] = k;
		}
		/* determine the lcm of all of the indeces */
		for (j = 0; j < factors_used_len; j++) {
			common_lcm = lcm(common_lcm, indeces[j]);
		}
		/* print result */
		printf((i == cases - 1) ? "%u\n" : "%u ", common_lcm);
	}
	return 0;
}
