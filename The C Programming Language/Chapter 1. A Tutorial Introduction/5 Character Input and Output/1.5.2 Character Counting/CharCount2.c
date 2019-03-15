#include <stdio.h>

/* count characters in input, 2nd version. */
int main(void)
{
	double nc;
	
	for (nc = 0; getchar() != '\n'; nc++)
		;
	printf("%.0f\n", nc);
}