/* Exercise 1-17. Write a program to print all input lines that are longer
	than 80 characters. This version doesn't count the \n as a character. */

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
	
	putchar('\n');
	
	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
		
		if (len > 80)
		{
			printf("The following line is longer than 80 characters:\n\"%s\"\n\n", line);
		}
	}

	if (max > 0)	/* there was a line */
	{
		printf("The longest line was:\n\"%s\"", longest);
		printf("\nThat line was %d characters long!", max);
	}
	
	putchar('\n');
	
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
	
	s[i] = '\0';
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