#include <limits.h> /* gives us CHAR_BIT */
#include <stdint.h> /* gives us int32_t */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	unsigned short int cases, i;
	/* get the number of cases from input */
	if (1 != scanf("%hu\n", &cases)) {
		fprintf(stderr, "error reading number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < cases; i++) {
		int32_t number;
		unsigned char j, sum;
		/* get the number from input */
		if (1 != scanf("%d", &number)) {
			fprintf(stderr, "error reading number %hu on line 2\n", i + 1);
			exit(EXIT_FAILURE);
		}
		/* sizeof number returns the number of char in number, and CHAR_BIT
		 * tells us how many bits are in a char. Therefore, CHAR_BIT*sizeof
		 * number gives us the number of bits in number. We loop through each
		 * bit, incrementing the sum if the bit is 1, or adding 0 if it's 0. */
		for (j = 0, sum = 0; j < CHAR_BIT*sizeof number; j++) {
			sum += number & 1; /* if LSB is 1, adds one; else adds nothing */
			number >>= 1; /* right shift the number by 1 */
		}
		/* print the results */
		printf((i == cases - 1) ? "%hu\n" : "%hu ", sum);
	}
	return 0;
}
