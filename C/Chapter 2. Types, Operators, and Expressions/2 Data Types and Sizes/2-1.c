/* Exercise 2-1. Write a program to determine the ranges of char, short, int
	and long variables, both signed and unsigned, by printing appropriate
	values from standard headers and direct computation. Harder if you compute
	them: determine the ranges of the various floating-point types. */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
	printf("signed char range:            [%d, %d]\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char range:          [%u, %u]\n", 0, UCHAR_MAX);
	printf("signed short int range:       [%d, %d]\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short int range:     [%u, %u]\n", 0, USHRT_MAX);
	printf("signed int range:             [%d, %d]\n", INT_MIN, INT_MAX);
	printf("unsigned int range:           [%u, %u]\n", 0, UINT_MAX);
	printf("signed long int range:        [%ld, %ld]\n", LONG_MIN, LONG_MAX);
	printf("unsigned long int range:      [%u, %lu]\n", 0, ULONG_MAX);
	printf("signed long long int range:   [%lld, %lld]\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long int range: [%u, %llu]\n", 0, ULLONG_MAX);
	printf("float range:                  [%.47f, %f]\n", FLT_MIN, FLT_MAX);
	printf("double range:                 [%.324f, %f]\n", DBL_MIN, DBL_MAX);
}