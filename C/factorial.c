#include<stdio.h>

unsigned long long int recur_fact(unsigned int input);
unsigned long long int iter_fact(unsigned int input);

int main(void)
{
	unsigned int n = 20;	// runs into integer overflow for any number > 20
	printf("%u factorial, using the recursive method, is %llu\n",
		n, recur_fact(n));
	printf("%u factorial, using the iterative method, is %llu\n",
		n, iter_fact(n));
	return 0;
}

unsigned long long int recur_fact(unsigned int n)
{
	if(n == 1) return n;

	else return n*recur_fact(n-1);
}

unsigned long long int iter_fact(unsigned int n)
{
	unsigned long long int fact = (unsigned long long int)n;

	for ( ; n > 1; n--)
	{
		fact *= (n - 1);
	}

	return fact;
}