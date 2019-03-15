#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 4096
#define MAX_NUMS 1024
#define MODULO 10000007
#define MULTIPLY 113

int main(void) {
	/* declare/initialize variables */
	size_t i, n_values;
	char input[MAX_LINE], *input_position;
	unsigned long checksum;
	/* determine number of values to sum from first line */
	fgets(input, MAX_LINE, stdin);
	n_values = strtoul(input, NULL, 10);
	/* get the second line, which contains all the values */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* Thanks to the magic property of modulus, we can take the modulus of the
	 * intermediate values and then modulo at the end and get the same result
	 * as if we hadn't done the intermediate moduli. This will prevent overflow
	 * from occurring */
	for (i = 0, checksum = 0; i < n_values; i++) {
		/* add the next value and take the modulus */
		checksum += strtoul(input_position, &input_position, 10);
		checksum %= MODULO;
		/* multiply by the multiplier and take the modulus again */
		checksum *= MULTIPLY;
		checksum %= MODULO;
	}
	/* print results */
	printf("%lu\n", checksum);
	return 0;
}
