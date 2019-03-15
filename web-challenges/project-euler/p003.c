/*******************************************************************************
 *
 * Largest prime factor
 *
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600851475143 ?
 *
 ******************************************************************************/

#include <stdio.h>
#define	SIZE	100	// indeces [0,99]
int primeFactor(unsigned long int num, unsigned long int *p2a);
int primeCheck(unsigned long int num);

int main(void) {
	unsigned long int factors[SIZE];
	const unsigned long int BIGNUM = 600851475143;

	for (int pre = 0; pre < SIZE; pre++) {
		*(factors+pre) = 0;
	}

	primeFactor(BIGNUM, factors);
	for (int i = 0; i < SIZE; i++) {	// i ends up being 100, at maximum
		printf("%lu ", factors[i]);
	}
	return 0;
}

// puts the prime factors of a number into the array, array[]
int primeFactor(unsigned long int num, unsigned long int *p2a) {
	int j = 0;
	for (unsigned long int i = 2; i <= num; i++) {
		while (num % i == 0) {
			num /= i;
			*(p2a+(j++)) = i;	// equivalent to p2a[j++] = i;
		}
	}
	return 0;
}
