/* external function test */

#include <stdio.h>

int main(void)
{
	char alphanum[] = "abc456";
	printf("%s\n", alphanum);
	
	reverse(alphanum);
	printf("%s", alphanum);
}