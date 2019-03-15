#include <stdio.h>

/* copy input to output, second version */

int main(void)
{
	int c;
	
	while ((c = getchar()) != 10)	/* 10 is the ASCII code for \n (could also use '\n'), which works great when running this script in the terminal (because newline == \n). EOF didn't work because hitting enter doesn't enter an EOF marker (=-1 in C), and although ctrl + z *should* work, it didn't. Not sure why. */
		putchar(c);
}