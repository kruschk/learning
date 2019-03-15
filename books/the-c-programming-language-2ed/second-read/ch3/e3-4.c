/******************************************************************************
 * As an example, consider a word size of 8:
 *     -(2^(8-1)) = -128 = 0b 1000 0000
 * When we negate this, the result in two's complement representation is:
 *     -(-128) = 0b 0111 1111 + 1 = 0b 1000 0000
 * So the result is the exact same number! This messes up the itoa algorithm
 * because the behaviour of % is funny with negative numbers. Also, the while 
 * condition would stop after the first iteration because the number was less
 * than 0.
 * The following code is from clc-wiki.net, but I figured out the reasoning!
 *****************************************************************************/
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
	int n = -2147483648;
	char s[MAX_LINE];

	itoa(n, s);
	printf("%s\n", s);

	return 0;
}

void itoa(int n, char s[]) {
	int sign = n;
	int i = 0;
	if (n >= 0) {
		do {
			s[i++] = n % 10 + '0';
		}
		while (n /= 10);
	}
	else {
		do {
			s[i++] = -(n % 10) + '0';
		}
		while (n /= 10);
	}

	if (sign < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';

	reverse(s);
}

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
