/*******************************************************************************
 *
 * Even Fibonacci numbers
 *
 * Each new term in the Fibonacci sequence is generated by adding the previous
 * two terms. By starting with 1 and 2, the first 10 terms will be:
 * 		1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
 * By considering the terms in the Fibonacci sequence whose values do not exceed
 * four million, find the sum of the even-valued terms.
 *
 ******************************************************************************/

#include <stdio.h>

int main(void) {
	unsigned int first = 0;
	unsigned int second = 1;
	unsigned int current;

	int sum = 0;
	for (current=first+second; current<=4000000; current=first+second) {
		if (current % 2 == 0) {
			printf("%u ", current);
			sum += current;
		}
		first = second;
		second = current;
	}
	printf("\n%d\n", sum);
}