/* Exercise 2-10. Rewrite the function lower, which converts upper case letters
	to lower case, with a conditional expression instead of if-else. */

#include <stdio.h>

char lower(char character);

int main(void)
{
	printf("%c", lower('t'));
	return 0;
}

char lower(char c)
{
	char z = (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
	return z;
}