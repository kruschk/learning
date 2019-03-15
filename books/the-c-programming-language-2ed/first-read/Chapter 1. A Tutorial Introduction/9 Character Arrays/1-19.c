/* Exercise 1-19. Write a function reverse(s) that reverses the character
	string s. Use it to write a program that reverses its input a line at a
	time. */

#include <stdio.h>
#define	MAXLINE	1000	/* Maximum number of characters */

int reverse(char string[], int string_length);

int main(void)
{
	int cont = 1;
	char input_line[MAXLINE];
	while (cont == 1)
	{
		cont = reverse(input_line, MAXLINE);
		putchar('\n');
	}
	
	return 0;
}

int reverse(char s[], int len)
{
	int i, j, c;
	char out[MAXLINE];
	
	c = 0;
	for (i = 0; i < len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = (char)c;
	
	--i;
	j = i;
	while (i >= 0)
	{
		out[j-i] = s[i];
		--i;
	}
	out[j+1] = '\0';
	
	i = 0;
	while (out[i] != '\0')
	{
		putchar(out[i]);
		++i;
	}
	
	if (c == EOF)
		return 0;
	else
		return 1;
}