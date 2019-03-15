#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

enum byte_status {CORRUPT = 0, OKAY};

/* check_parity: returns CORRUPT if the byte is corrupt, OKAY if it's not */
enum byte_status check_parity(unsigned char encoded_byte) {
	size_t i;
	char bit_sum = 0;
	/* count the number of 1 bits in encoded_byte; there are 8 bits in a
	 * byte (a char is equivalent to a byte) */
	for (i = 0; i < 8; i++) {
		bit_sum += encoded_byte & 1;
		encoded_byte >>= 1;
	}
	/* if the number of 1 bits is even, return OKAY, otherwise the byte is
	 * corrupt */
	if (bit_sum % 2 == 0) {
		return OKAY;
	}
	else {
		return CORRUPT;
	}
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	unsigned char encoded_byte;
	/* get the string into input and collect the first encoded byte */
	fgets(input, MAX_LINE, stdin);
	encoded_byte = strtoul(input, &input_position, 10);
	/* loop through the encoded bytes until we reach the end */
	while (encoded_byte != '.') {
		unsigned char normal_byte;
		/* if we have an uncorrupted byte, print it */
		if (check_parity(encoded_byte) == OKAY) {
			/* strip the MSB to get a normal byte (in the range [0, 127]) */
			normal_byte = encoded_byte & 0177;
			putchar(normal_byte);
		}
		/* get the next encoded byte */
		encoded_byte = strtoul(input_position, &input_position, 10);
	}
	/* print the terminating byte and a newline */
	putchar(encoded_byte);
	putchar('\n');
	return 0;
}
