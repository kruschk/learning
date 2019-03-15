/*******************************************************************************
 *
 * Smallest multiple
 *
 * 2520 is the smallest number that can be divided by each of the numbers from 1
 * to 10 without any remainder.
 * What is the smallest positive number that is evenly divisible by all of the
 * numbers from 1 to 20?
 *
 ******************************************************************************/

#include <stdio.h>

int checkUnique(int num);

int main(void) {
	for (int i = 2; i <= 1000000000; i++) {
		if (checkUnique(i)) {
			printf("%d\n", i);
		}
	}
	//printf("%d\n", checkUnique(232792560));
	return 0;
}

// returns 1 if num is evenly divisible by all of the numbers in range [1, lim]
int checkUnique(int num) {
	const int lim = 20;
	for (int i = 2; i <= lim; i++) {
		if (num % i == 0) {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}
