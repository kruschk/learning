#include <stdio.h>

/* Exercise 1-8: Write a program to count blanks, tabs, and newlines. */

int main(void)
{
	int c, bk, tb, nl;
	bk = 0;
	tb = 0;
	nl = 0;
	
	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
			++bk;
		else if (c == '\t')
			++tb;
		else if (c == '\n')
			++nl;
	}
	
	printf("Blanks: %d\n", bk);
	printf("Tabs: %d\n", tb);
	printf("Newlines: %d", nl);
}