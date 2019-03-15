/*******************************************************************************
 *
 * Largest palindrome product
 *
 * A palindromic number reads the same both ways. The largest palindrome made
 * from the product of two 2-digit numbers is 9009 = 91 × 99.
 * Find the largest palindrome made from the product of two 3-digit numbers.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palindrome(int);

int main(void) {
	int i, j;
	int result;
	for (i = 1; i < 999; i++) {
		for (j = 1; j < 999; j++) {
			if (palindrome(result = i * j)) {
				printf("%d * %d = %d\n", i, j, result);
			}
		}
	}
}

// returns 1 if the input number is a palindrome, 0 otherwise
int palindrome(int num) {
	char str[100];
	sprintf(str, "%d", num);	// converts the int to a character string
	size_t totlength = strlen(str);
	int halflength = totlength/2;
	for (int i = 0; i <= halflength; i++) {
		if (str[totlength-i-1] == str[i]) {	// -1 is req'd because of 0 offset
			;	// do nothing
		}
		else {
			return 0;
		}
	}
	return 1;
}
