#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* MAX_PRIME = floor(sqrt(9,999,999,999,999)), the largest 13-digit number */
#define MAX_PRIME 3162277

enum boolean {FALSE, TRUE};

/* is_prime: returns TRUE if the given number is a prime, FALSE otherwise. Uses
 * some Project Euler problem #7 magic. */
enum boolean is_prime(const unsigned long int n) {
	if (n == 1) { /* 1 is not a prime */
		return FALSE;
	}
	else if (n < 4) { /* 2, 3 */
		return TRUE;
	}
	else if (n%2 == 0) { /* even */
		return FALSE;
	}
	else if (n < 9) { /* 5, 7 */
		return TRUE;
	}
	else if (n%3 == 0) { /* divisible by 3 */
		return FALSE;
	}
	else {
		unsigned long int i;
		/* only need to test up to and including floor(sqrt(n)), but C
		 * truncates fractional part by default */
		unsigned long int root = sqrt(n);
		/* all primes greater than 3 can be written in the form 6*k+/-1; since
		 * we only need to divide by prime factors, it suffices to only check
		 * all the 6*k+/-1 values up to and including floor(sqrt(n)) */
		for (i = 5; i <= root; i += 6) {
			if (n%i == 0) { /* 6*k - 1 */
				return FALSE;
			}
			else if (n%(i+2) == 0) { /* 6*k + 1 */
				return FALSE;
			}
		}
		/* if we haven't returned yet, it must be a prime */
		return TRUE;
	}
}

/* generate_prime_array: write the first n primes to array */
void generate_prime_array(unsigned long int *primes[], size_t *primes_size,
		size_t *end_length, const unsigned long int max_prime) {
	/*size_t i, n_primes = 65536 - 1;*/ /* 2^16-1 */
	size_t i;
	unsigned long int test;
	/*unsigned long int *primes = malloc(n_primes*(sizeof *primes));*/
	(*primes)[0] = 2; /* 2 is the first, and only even, prime */
	/* only need to check odd numbers after 2 has been accounted for */
	for (i = 1, test = 3; test <= max_prime; test += 2) {
		/* test for primality */
		if (is_prime(test)) {
			/* add test to the array if appropriate */
			(*primes)[i] = test;
			i++;
			/* reallocate memory if we've run out of space */
			if (i >= *primes_size) {
				*primes_size = 2*(*primes_size + 1) - 1;
				*primes = realloc(*primes, *primes_size*(sizeof **primes));
			}
		}
	}
	/* store the length of the array in end_length */
	*end_length = i;
	return;
}

int main(void) {
	unsigned long int n_cases;
	size_t last_index, i;
	size_t n_primes = 65536 - 1; /* 2^16-1 */
	size_t n_factors = n_primes;
	/* allocate memory */
	unsigned long int *primes = malloc(n_primes*(sizeof *primes));
	unsigned long int *factors = malloc(n_factors*(sizeof *factors));
	/* get the number of cases */
	scanf("%lu\n", &n_cases);
	/* generate the array of primes */
	generate_prime_array(&primes, &n_primes, &last_index, MAX_PRIME);
	/* factor the given number for each test case */
	for (i = 0; i < n_cases; i++) {
		unsigned long int num;
		size_t j, k, factors_len;
		/* get the primes which we want to factor */
		scanf("%lu\n", &num);
		/* find them using the generated prime array */
		for (j = 0, k = 0; num != 1 && j < last_index; j++) {
			/* if num is evenly divisible by the jth prime, add the prime to
			 * factors and set num to the num divided by that prime */
			while (num != 1 && num%primes[j] == 0) {
				factors[k] = primes[j];
				k++;
				num /= primes[j];
				/* reallocate factors array if required */
				if (k >= n_factors) {
					n_factors = 2*(n_factors + 1) - 1;
					factors = realloc(factors, n_factors*(sizeof *factors));
				}
			}
		}
		factors_len = k;
		/* print results */
		for (k = 0; k < factors_len; k++) {
			printf((k == factors_len - 1) ? "%lu" : "%lu*", factors[k]);
		}
		putchar((i == n_cases - 1) ? '\n' : ' ');
	}
	/* free memory */
	free(primes);
	free(factors);
	return 0;
}
