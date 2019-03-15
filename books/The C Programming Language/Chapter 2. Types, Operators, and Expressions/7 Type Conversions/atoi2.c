/* atoi: convert s to integer s */

#include <stdio.h>
int atoi2(char string[]);

int main(void)
{
	printf("%d", atoi2("0697238154"));
	return 0;
}

int atoi2(char s[])
{
	int i, n;
	
	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
	{
		n = 10 * n + (s[i] - '0');
	}
	return n;
}
