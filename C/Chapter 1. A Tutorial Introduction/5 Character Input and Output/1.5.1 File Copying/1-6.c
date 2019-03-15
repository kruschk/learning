#include <stdio.h>

/* print the value of getchar() != EOF or getchar() == EOF */

int main(void)
{
	printf("%d\n", getchar() != EOF);
	printf("%d", getchar() == EOF);
}