#include <stdio.h>

int strlen(char input_string[]);

int main(void)
{
	char string = "This is a string?";
	printf("%d", strlen(string));
	return 0;
}

int strlen(char s[])
{
	int i = 0;
	while (s[i] != 0)
	{
		++i;
	}
	return i;
}