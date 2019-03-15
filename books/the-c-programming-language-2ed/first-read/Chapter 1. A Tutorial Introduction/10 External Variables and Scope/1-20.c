/* Exercise 1-20. Write a program detab that replaces tabs in the input with
	the proper number of blanks to space to the next tab stop. Assume a fixed
	set of tab stops, say every n columns. Should n be a variable or a symbolic
	parameter? */ /* n should be a symbolic parameter. */

#include <stdio.h>
#define	TAB	4	/* tab stop will be every TAB-th column */

void detab(int tab_size, int column_index);

int main(void)
{
	int c, ncol;
	ncol = 0;
	
	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			detab(TAB, ncol);
			ncol = 0;
		}
		else if (c == '\n')
		{
			ncol = 0;
			putchar(c);
		}
		else
		{
			++ncol;
			putchar(c);
		}
	}

	return 0;
}

void detab(int tab_size, int column_index)
{
	int i = 0;
	int remain = tab_size - column_index % tab_size;
	
	while (i < remain)
	{
		putchar(' ');
		++i;
	}
}