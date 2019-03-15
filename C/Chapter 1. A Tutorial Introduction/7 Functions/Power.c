#include <stdio.h>

int power(int m, int n);

/* test power function */
int main(void)
{
	for (int i = 0; i < 10; ++i)
		printf("%d %3d %6d\n", i, power(2, i), power(-3, i));
	return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base,int n)
{
	int p;
	
	p = 1;
	for (int i = 1; i <= n; i++)
		p = p * base;
	return p;
}