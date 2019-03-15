/* Exercise 3-2. Write a function escape(s,t) that converts characters like
	newline and tab into visible escape sequences like \n and \t as it copies
	the string t to s. Use a switch. Write a function for the other direction
	as well, converting escape sequences into the real characters. */

#include <stdio.h>
#define	MAXLENGTH	1000

void escape (char s[], char t[]);
void unescape (char s[], char t[]);

int main(void)
{
	char copyfrom[] = "This\n	\tis a\nstrin\\g to\nbe formatted.";
	char copyto[MAXLENGTH];
	printf("Original string:\n%s\n\n", copyfrom);
	escape(copyfrom, copyto);
	printf("Formatted string:\n%s\n\n", copyto);
	unescape(copyto, copyfrom);
	printf("Formatted string returned to original:\n%s", copyfrom);
}

void escape (char s[], char t[])
{
	int c, i, j;
	
	i = j = 0;
	while ((c = s[i]) != '\0')
	{
		switch (c)
		{
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			default:
				t[j++] = (char)c;
				break;
		}
		i++;
	}
	t[j] = '\0';
}

void unescape (char s[], char t[])
{
	int i, j;
	
	i = j = 0;
	while (s[i] != '\0')
	{
		switch (s[i])
		{
			case '\\':	/* if the current character is a backslash */
				if (s[i+1] == 't')
				{
					t[j++] = '\t';
					i++;
				}
				else if (s[i+1] == 'n')
				{
					t[j++] = '\n';
					i++;
				}
				else
				{
					t[j++] = s[i];
				}
				break;
			default:
				t[j++] = s[i];
				break;
		}
		i++;
	}
	t[j] = '\0';
}