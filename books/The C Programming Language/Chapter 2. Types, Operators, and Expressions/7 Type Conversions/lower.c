/* lower: convert c to lower case; ASCII only */

#include <stdio.h>

int lower(int character);

int main(void)
{
	printf("%c", lower('G'));
	return 0;
}

int lower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + 'a' - 'A';
	}
	else
		return c;
}