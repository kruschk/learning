/* Exercise 2-2. Write a loop equivalent to the for loop above without using &&
	or ||. */

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
		printf("%s", longest);

	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	
	i = 0;
	while (i < lim - 1)
	{
		c = getchar();
		if (c == '\n')
		{
			break;
		}
		else if (c == EOF)
		{
			break;
		}
		else
		{
			s[i] = (char)c;
			++i;
		}
	}
	
	/* {
		s[i] = (char)c;
	} */
	if (c == '\n')
	{
		s[i] = (char)c;
		i++;
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