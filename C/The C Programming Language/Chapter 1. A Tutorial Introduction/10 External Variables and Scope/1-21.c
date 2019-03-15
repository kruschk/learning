/* Exercise 1-21. Write a program entab that replaces strings of blanks by the
	minimum number of tabs and blanks to achieve the same spacing. Use the same
	tab stops as for detab. when either a tab or a single blank would suffice
	to reach a tab stop, which should be given preference? 1-21<1-21in.txt>1-21out.txt */

#include <stdio.h>
#define	TAB	4	/* tab stop will be every TAB-th column */

void entab(int column_index, int blank_count);

int main(void)
{
	int c, ncol, nblank;
	
	ncol = nblank = 0;
	while ((c = getchar()) != EOF)
	{
		++ncol;
		if (c == ' ')
		{
			++nblank;
			if (nblank >= TAB)
			{
				entab(ncol, nblank);
			}
			else
			{
				putchar(c);
			}
		}
		else if (c == '\n')
		{
			ncol = nblank = 0;
			putchar(c);
		}
		else
		{
			putchar(c);
		}
	}
	
	return 0;
}

void entab(int column_index, int blank_count)
{	
	while (blank_count >= TAB)
	{
		putchar('\t');
		blank_count = blank_count - TAB;
	}
	
	if (blank_count > 0)
	{
	}
}