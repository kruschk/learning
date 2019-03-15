/******************************************************************************
 * In consider a short count in two's complement:
 *     ...
 *     000...00011 = +3
 *     000...00010 = +2
 *     000...00001 = +1
 *     000...00000 =  0
 *     111...11111 = -1
 *     111...11110 = -2
 *     111...11101 = -3
 *     ...
 * From this pattern, we can see that e.g. taking +3 and masking it by +2 will
 * produce:
 *     000...00011
 *     000...00010
 *     &----------
 *     000...00010
 * Masking this again with the +1 results in:
 *     000...00010
 *     000...00001
 *     &----------
 *     000...00000
 * At this point we can compare the result to zero and complete our loop. With
 * an iteration counter in that loop, note that the number of iterations
 * matches the number of bits in the starting number. Magic.
 *****************************************************************************/

#include <stdio.h>

int bitcount(unsigned x);
int bitcount2(unsigned x);

int main(void) {
	int x = 1;
	int result = bitcount(x);
	int result2 = bitcount2(x);
	printf("bitcount: %d\nbitcount2: %d\n", result, result2);

	return 0;
}

int bitcount(unsigned x) {
	int b;

	for (b = 0; x != 0; x >>= 1) {
		if (x & 1) {
			++b;
		}
	}

	return b;
}

int bitcount2(unsigned x) {
	int b;

	for (b = 0; x != 0; x &= x - 1) {
		++b;
	}

	return b;
}
