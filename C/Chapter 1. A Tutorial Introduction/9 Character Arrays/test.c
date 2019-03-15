#include <stdio.h>

void trim(void);
void trimtrailing(void);

int main(void)
{
	trimtrailing();	
	return 0;
}

void trim(void)
{
	int last, next;
	
	last = 0;
	while ((next = getchar()) != EOF)
	{
		if (next == ' ' && last == ' ')
		{
			;
		}
		else
		{
			putchar(next);
			last = next;
		}
	}
}

void trimtrailing(void)
{
	int i, ch;
	char str[1000];
	
	for (i = 0; i < 999 && (ch = getchar()) != EOF && ch != '\n'; i++)
	{
		str[i] = (char)ch;
	}
	
	while (str[--i] == ' ')
	{
		;
	}
	
	str[++i] = '\0';
	
	printf("\"%s\"", str);
}