/* Exercise 1-9: Write a program to copy its input to its output, replacing
	each string of one or more blanks by a single blank. */

#include <stdio.h>

int main(void)
{
	int c, d;
	
	while ((c = getchar()) != EOF)				// while next character != EOF
	{
		if (c == ' ')							// if that character is a space:
		{
			while ((d = getchar()) == ' ')		// loop through the spaces and ignore all of them, variable d will end up being the first character of the next word, so we store it.
				;
			putchar(' ');						// put a single space where there was once one or several.
			putchar(d);							// print the first letter of the next word.
		}
		else
			putchar(c);							// otherwise, just print the next character.
	}
	
	return 0;
}