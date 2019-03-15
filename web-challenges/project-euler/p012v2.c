#include <stdio.h>

unsigned long int triangularNumber(unsigned long int n);
unsigned long int divisorCount(unsigned long int n);

int main(void) {
	unsigned long int divisors = 0;
	for (size_t i = 7278; divisors <= 500; i++) {
		unsigned long int triangular = triangularNumber(i);
		divisors = divisorCount(triangular);
		printf("i: %lu\ttriangular number: %lu\t# of divisors: %lu\n", i, triangular, divisors);
	}

	//printf("%lu\n", divisorCount(14619084));
	return 0;
}

unsigned long int triangularNumber(unsigned long int n) {
	unsigned int sum = 0;
	for (size_t i = 1; i <= n; i++) {
		sum += i;
	}
	return sum;
}

unsigned long int divisorCount(unsigned long int n) {
	unsigned long int divisorCount = 2; // we know that 1 and n are both divisors, no need to calculate them
	for (size_t i = 2; i <= n/2; i++) {
		if (n % i == 0) {
			//printf("\tn: %lu\ti: %lu\n", n, i);
			//c /= i;
			divisorCount += 1;
		}
	}

	return divisorCount;
}
