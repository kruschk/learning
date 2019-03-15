/* Exercise 1-13: Write a program to print a histogram of the lengths of words
	in its input. It is easy to draw the histogram with the bars horizontal, a
	vertical orientation is more challenging. */

#include <stdio.h>

#define	ARRAYLEN	10	/* length of the array, longest word can only
							be as many chars as ARRAYLEN */
#define	IN			1	/* inside a word */
#define	OUT			0	/* outside a word */
	
int main(void)
{
	int c, i, j, nchar, state;
	int yaxis[ARRAYLEN];
	
	for (i = 0; i < ARRAYLEN; ++i)
	{
		yaxis[i] = 0;
	}
	
	
	/* 
	if state goes from IN to OUT:
		state = OUT;
		nchar = 0;
		++yaxis[nchar]
		
	if state goes from OUT to IN:
		state = IN
		++nchar

	if state goes from IN to IN:
		++nchar
		
	if state goes from OUT to OUT:
		do nothing
	*/
	state = OUT;
	nchar = 0;
	while ((c = getchar()) != '~')
	{
		/* state goes from IN to OUT */
		if (state == IN && (c == ' ' || c == '\t' || c == '\n'))
		{
			state = OUT;
			++yaxis[nchar-1];
			nchar = 0;
		}
		/* state goes from OUT to IN */
		else if (state == OUT && c != ' ' && c != '\t' && c != '\n')
		{
			state = IN;
			++nchar;
		}
		/* state goes from IN to IN */
		else if (state == IN && c != ' ' && c != '\t' && c != '\n')
		{
			++nchar;
		}
	}
	
	putchar('\n');
	
	/* print the histogram */
	for (i = 0; i < ARRAYLEN; ++i)
	{
		/* print the y-axis */
		printf("%2d ", i + 1);
		
		if (yaxis[i] >= 0)
		{
			j = 0;
			/* print the corresponding frequency of words */
			while (j < yaxis[i])
			{
				putchar('-');
				++j;
			}
			putchar('\n');
		}
		else
			putchar('\n');
	}

	return 0;
}