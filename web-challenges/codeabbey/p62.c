#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_PRIME 3000000

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
unsigned long int *generate_prime_array(size_t *end_length,
		const unsigned long int max_prime) {
	size_t i, n_primes = 65536 - 1; /* 2^16-1 */
	unsigned long int test;
	unsigned long int *primes = malloc(n_primes*(sizeof *primes));
	primes[0] = 2; /* 2 is the first, and only even, prime */
	/* only need to check odd numbers after 2 has been accounted for */
	for (i = 1, test = 3; test <= max_prime; test += 2) {
		/* test for primality */
		if (is_prime(test)) {
			/* add test to the array if appropriate */
			primes[i] = test;
			i++;
			/* reallocate memory if we've run out of space */
			if (i >= n_primes) {
				n_primes = (n_primes + 1)*2 - 1;
				primes = realloc(primes, n_primes*(sizeof *primes));
			}
		}
	}
	/* store the length of the array in end_length */
	*end_length = i;
	/* return a pointer to the array */
	return primes;
}

/* binsearch: simple implementation of a binary search which finds value in
 * array between low and high and stores the index in return_index if the value
 * is found */
enum boolean binsearch(unsigned long int *array, unsigned long int value,
		size_t low, size_t high, size_t *return_index) {
	size_t mid = (low + high)/2;
	while (low < high) {
		if (value < array[mid]) {
			high = mid;
			mid = (low + high)/2;
		}
		else if (value > array[mid]) {
			low = mid;
			mid = (low + high)/2;
		}
		else {
			*return_index = mid;
			return TRUE;
		}
	}
	return FALSE;
}

int main(void) {
	unsigned long int *primes;
	unsigned long int n_cases;
	size_t last_index, i;
	/* get the number of cases */
	scanf("%lu\n", &n_cases);
	/* generate the array of primes */
	primes = generate_prime_array(&last_index, MAX_PRIME);
	/* fetch the count of the number of primes within the range [a, b] for each
	 * test case */
	for (i = 0; i < n_cases; i++) {
		unsigned long int a, b;
		size_t a_index, b_index;
		/* get the primes which we want to find */
		scanf("%lu %lu\n", &a, &b);
		/* find them in the generated prime array */
		if (binsearch(primes, a, 0, last_index - 1, &a_index) == TRUE
				&& binsearch(primes, b, 0, last_index - 1, &b_index) == TRUE) {
			size_t prime_count = b_index - a_index + 1;
			/* print the result */
			printf((i == n_cases - 1) ? "%lu\n" : "%lu ", prime_count);
		}
		else {
			fprintf(stderr, "error: couldn't find primes\n");
		}
	}
	free(primes);
	return 0;
}
