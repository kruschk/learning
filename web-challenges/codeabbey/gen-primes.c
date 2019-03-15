#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gen-primes.h"
/* MAX_PRIME = floor(sqrt(9,999,999,999,999)), the largest 13-digit number */
#define MAX_PRIME 3162277

/* is_prime: returns TRUE if the given number is a prime, FALSE otherwise. Uses
 * some Project Euler problem #7 magic. */
enum boolean is_prime(const unsigned int n) {
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
		unsigned int i;
		/* only need to test up to and including floor(sqrt(n)), but C
		 * truncates fractional part by default */
		unsigned int root = sqrt(n);
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

/* generate_prime_array: write all the primes up to max_prime into the array
 * primes, which has initial length array_length, and store the occupied length
 * of the array in used_length. */
void generate_prime_array(unsigned int *primes[], size_t *array_length,
		size_t *used_length, const unsigned int max_prime) {
	size_t i;
	unsigned int test;
	(*primes)[0] = 2; /* 2 is the first, and only even, prime */
	/* only need to check odd numbers after 2 has been accounted for */
	for (i = 1, test = 3; test <= max_prime; test += 2) {
		/* test for primality */
		if (is_prime(test)) {
			/* add test to the array if appropriate */
			(*primes)[i] = test;
			i++;
			/* reallocate memory if we've run out of space */
			if (i >= *array_length) {
				*array_length = 2*(*array_length + 1) - 1;
				*primes = realloc(*primes, *array_length*(sizeof **primes));
			}
		}
	}
	/* store the length of the array in end_length */
	if (used_length != NULL) {
		*used_length = i;
	}
	return;
}
