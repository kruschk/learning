#include <stddef.h>
unsigned long int checksum(const unsigned long multiplier, const unsigned long divisor, const long int *array, size_t length) {
	size_t i;
	unsigned long int checksum;
	for (i = 0, checksum = 0; i < length; i++) {
		/* add the next value and take the modulus */
		checksum += array[i];
		checksum %= divisor;
		/* multiply by the multiplier and take the modulus again */
		checksum *= multiplier;
		checksum %= divisor;
	}
	return checksum;
}
