#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
	printf("Integers:\n");

	/* char: */
	printf("Unsigned char: (%hu, %hu)\n", 0, UCHAR_MAX);
	printf("Signed char: (%+d, %+d)\n", SCHAR_MIN, SCHAR_MAX);

	/* short: */
	printf("Unsigned short: (%hu, %hu)\n", 0, USHRT_MAX);
	printf("Signed short: (%+hd, %+hd)\n", SHRT_MIN, SHRT_MAX);

	/* int: */
	printf("Unsigned int: (%u, %u)\n", 0, UINT_MAX);
	printf("Signed int: (%+d, %+d)\n", INT_MIN, INT_MAX);

	/* long: */
	printf("Unsigned long: (%u, %lu)\n", 0, ULONG_MAX);
	printf("Signed long: (%+ld, %+ld)\n", LONG_MIN, LONG_MAX);

	printf("\nFloating point numbers:\n");
	/* float: */
	printf("Float: (%G, %G)\n", FLT_MIN, FLT_MAX);

	/* double: */
	printf("Double: (%G, %G)\n", DBL_MIN, DBL_MAX);


	printf("Long double: (%LG, %LG)\n", LDBL_MIN, LDBL_MAX);
	return 0;
}
