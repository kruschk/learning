/* Exercise 1-14: Write a program to print a histogram of the frequencies of
	different characters in its input.  Exercise1-14hori.c "Sphinx of black quartz, judge my vow." */

#include <stdio.h>
#define	UPPER	127		/* upper bound of the array */
#define LOWER	32		/* lower bound of the array */
#define RANGE	UPPER - LOWER + 1	/* defines the range of ASCII chars we're interested in. */

int main(void)
{
	int c, i, j;
	int count[RANGE];
	
	for (i = LOWER; i < UPPER; ++i)
		count[i] = 0;
	
	while ((c = getchar()) != EOF)
	{
		for (i = 32; i < 127; ++i)
			if (c == i)
				++count[i];
	}
	
	for (i = LOWER; i < UPPER; ++i)
	{
		printf("%c: ", i);
		j = 0;
		while (j < count[i])
		{
			putchar('-');
			++j;
		}
		putchar('\n');
	}
	
	return 0;
}