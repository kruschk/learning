#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_STRUCTS 1024

struct sign_value {
	char sign;
	unsigned long value;
};

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	size_t i = 0, n_sign_values;
	struct sign_value struct_array[MAX_STRUCTS];
	unsigned long result, modulus;
	/* get the first number and convert it to unsigned long */
	fgets(input, MAX_LINE, stdin);
	result = strtoul(input, NULL, 10);
	/* populate struct_array */
	while (fgets(input, MAX_LINE, stdin) != NULL && i < MAX_STRUCTS) {
		struct_array[i].sign = input[0];
		struct_array[i].value = strtoul(&input[2], NULL, 10);
		i++;
	}
	n_sign_values = --i; /* so we know how many structs to go through */
	modulus = struct_array[n_sign_values].value; /* this is the modulus value */
	/* compute result, computing modulus of each intermediate step so numbers
	 * don't grow too large */
	for (i = 0; i < n_sign_values; i++) {
		switch (struct_array[i].sign) {
			case '+':
				result = (result + struct_array[i].value) % modulus;
				break;
			case '*':
				result = (result*struct_array[i].value) % modulus;
				break;
			case '%':
				result %= struct_array[i].value;
				break;
			default:
				break;
		}
	}
	/* format printing so there's no trailing space */
	printf("%lu\n", result);
	return 0;
}
