#include <math.h>
#include <stdio.h>
#define MAX_N_PRIMES 200000

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
void generate_prime_array(unsigned long int array[], unsigned long int n) {
	size_t i;
	unsigned long int test;
	array[0] = 2; /* 2 is the first, and only even, prime */
	/* only need to check odd numbers after 2 has been accounted for */
	for (i = 1, test = 3; i < n; i++, test += 2) {
		/* loop until a prime is found */
		while (!is_prime(test)) {
			test += 2;
		}
		/* reach this once we've found a prime */
		array[i] = test;
	}
}

int main(void) {
	/* static declaration prevents stack overflow when MAX_N_PRIMES is very
	 * large (~2,000,000). I believe stack overflow occurs because main is a
	 * function like any other, and it can only have a limited function frame
	 * size. Declaring the array as static allocates the memory in .data
	 * instead of on the stack, which avoids the issue. */
	static unsigned long int primes[MAX_N_PRIMES];
	unsigned long int n_cases;
	size_t i;
	/* get the number of cases */
	scanf("%lu\n", &n_cases);
	/* generate the array of primes */
	generate_prime_array(primes, MAX_N_PRIMES);
	/* fetch the given prime for each test case */
	for (i = 0; i < n_cases; i++) {
		size_t index;
		scanf("%lu ", &index); /* get the index */
		index--; /* indeces are 1-indexed, so adjust to 0-indexing */
		/* print the result */
		printf((i == n_cases - 1) ? "%lu\n" : "%lu ", primes[index]);
	}
	return 0;
}
