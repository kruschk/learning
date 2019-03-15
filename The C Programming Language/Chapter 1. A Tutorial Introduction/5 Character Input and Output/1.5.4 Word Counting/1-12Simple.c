/* Exercise 1-12: Write a program that prints its input one word per line. */

#include <stdio.h>

#define	IN	1	/* inside a word */
#define	OUT	0	/* outside a word */

int main(void)
{
	int c, state;
	
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			putchar('\n');
		}
		else
		{
			putchar(c);
		}
	}
	return 0;
}