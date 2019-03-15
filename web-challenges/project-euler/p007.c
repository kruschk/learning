/*******************************************************************************
 *
 * 10001st prime
 *
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
 * the 6th prime is 13.
 * What is the 10 001st prime number?
 *
 ******************************************************************************/

#include <stdio.h>
#define	LIMIT	10001

int checkPrime(unsigned long int num);

int main(void) {
	int count = 0;
	for (unsigned long int i = 2; count < LIMIT; i++) {
		if (checkPrime(i)) {
			count++;
			printf("Prime #%d is %lu\n", count, i);
		}
	}
}

// returns 1 if a number is prime, 0 otherwise. Only accepts numbers >= 2
int checkPrime(unsigned long int num) {
	for (unsigned long int j = 2; j < num; j++) { // 0, 1, 2 will all return 1
		if (num % j == 0) {
			return 0;
		}
	}
	return 1;
}
