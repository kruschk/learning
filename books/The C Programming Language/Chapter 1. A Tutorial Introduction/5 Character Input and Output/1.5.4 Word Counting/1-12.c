/* Exercise 1-12: Write a program that prints its input one word per line. */

#include <stdio.h>

#define	IN	1	/* inside a word */
#define	OUT	0	/* outside a word */

int main(void)
{
	int c, state;
	
	state = IN;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			putchar('\n');
			putchar(c);
		}
		else
			putchar(c);
	}
	return 0;
}