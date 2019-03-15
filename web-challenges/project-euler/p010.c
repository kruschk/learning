#include <stdio.h>
#include <stdbool.h>

bool checkIfPrime(unsigned long int n);
unsigned long int sumOfPrimes(unsigned long int low, unsigned long int high);

int main(void) {
	const unsigned long int MIN = 2; // algorithm will not work if MIN < 2.
	const unsigned long int MAX = 10;
	unsigned long int sum = 0;
	/*for (unsigned long int i = 2; i < MAX; i++) {
		if (checkIfPrime(i)) {
			sum += i;
			printf("i: %lu\trun sum: %lu\n", i, sum);
		}
	}*/

	sum = sumOfPrimes(MIN, MAX);

	printf("sum: %lu\n", sum);

	return 0;
}

bool checkIfPrime(unsigned long int n) {
	for (unsigned long int i = 2; i < n/2+1; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

unsigned long int sumOfPrimes(unsigned long int low, unsigned long int high) {
	/* if (low >= high) {
		return 0;
	}
	if (low == 0) {

	}
	if (low == 1) {

	} */
	unsigned long int sum = 0;
	for (unsigned long int i = low; i < high; i++) {
		if (checkIfPrime(i)) {
			sum += i;
			printf("count: %lu\trunning sum: %lu\n", i, sum);
		}
	}
	return sum;
}
