/* strcat: concatenate t to the end of s; s must be big enough */
#include <stdio.h>
void strcat(char s[], char t[]);

int main(void)
{
	char s[] = "Short strings";
	char t[] = " only!";
	strcat(s, t);
	for (int i = 0; s[i] != '\0'; i++)
	{
		putchar(s[i]);
	}
}

void strcat(char s[], char t[])
{
	int i, j;
	
	i = j = 0;
	while (s[i] != '\0')	/* find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0')
		;
}