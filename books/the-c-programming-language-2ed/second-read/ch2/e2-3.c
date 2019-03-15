#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BASE 16

unsigned long int htoi(const char hexadecimal[]);
unsigned long int power(const unsigned int base, unsigned int exponent);

int main(void) {
	const char hex_num[] = "0xabcdef123456789";

	printf("%s in hexadecimal is: %lx\n", hex_num, htoi(hex_num));

	return 0;
}

/******************************************************************************
 * htoi: converts a hexadecimal string into an integer.
 *
 * Input:
 * -A character string representing a hexadecimal integer number.
 *
 * Output:
 * -The integer value of the hexadecimal string.
 *
 * Known bugs:
 * -Currently does not support leading 0x or 0X notation.
 * -Does not handle negative numbers.
 * -Doesn't handle "hexadecimal" points (not really a bug as it is intended for
 *  integers).
 *****************************************************************************/
unsigned long int htoi(const char hexadecimal[]) {
	unsigned long int exponent = 0;
	int i;
	unsigned long int return_value = 0;
	size_t len = strlen(hexadecimal);

	for (i = len - 1; i >= 0; --i) {
		/* guard against invalid inputs */
		unsigned char c = tolower(hexadecimal[i]);
		unsigned long int significand;
		if (!(('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || c == 'x')) {
			printf("invalid input to htoi()!\n");
			return -1;
		}

		/* set the significand to the desired value */
		if ('0' <= c && c <= '9') {
			significand = c - '0';
		}
		else if ('a' <= c && c <= 'f') {
			significand = c - 'a' + 10;
		}
		else if (c == 'x') {
			if (i == 1 || hexadecimal[0] == '0') {
				break;
			}
			else {
				printf("invalid input to htoi()!\n");
			}
		}

		/* calculate the running total */
		return_value += significand*power(BASE, exponent);
		++exponent;
	}

	return return_value;
}

/******************************************************************************
 * power: returns base to the power of exponent, where all values are positive.
 *
 * Input:
 * -base, which is a strictly positive integer.
 * -exponent, a nonnegative integer (i.e. may be positive or zero).
 *
 * Output:
 * -base to the power of exponent
 *
 * Known bugs:
 * -Bad things happen if a negative number is passed as the exponent due to a
 * silent conversion to a large unsigned value.
 *****************************************************************************/
unsigned long int power(const unsigned int base, unsigned int exponent) {
	unsigned long int result = 1;

	while (exponent > 0) {
		result *= base;
		--exponent;
	}

	return result;
}
