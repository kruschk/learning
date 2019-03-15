/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each
	line of input, and to delete entirely blank lines. This version doesn't
	count the \n as a character. */
	
#include <stdio.h>
#define	MAXLINE	1000	/* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main(void)
{
	int len;				/* current line length */
	int max;				/* maximum length seen so far */
	char line[MAXLINE];		/* current input line */
	char longest[MAXLINE];	/* longest line saved here */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0)	/* there was a line */
	{
		printf("The longest line was:\n\"%s\"", longest);
		printf("\nThat line was %d characters long!", max);
	}
	
	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		s[i] = (char)c;
	}
	
	while (s[--i] == ' ' || s[i] == '\t')		/* since the test condition
		evaluates left-to-right, i is decremented in the test on the left, so
		i=i-1, then on the right there is no need to decrement again. */
	{
		;
	}
	
	s[++i] = '\0';
	
	return i;
}

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from[])
{
	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0')
	{
		i++;
	}
}