#include <stdio.h>

/* copy input to output, first version */

int main(void)
{
	int c;
	
	c = getchar();
	while (c != EOF)		/* 10 is the ASCII code for \n (could also use '\n'), which works great when running this script in the terminal (because enter key == \n). EOF didn't work because hitting enter doesn't enter an EOF marker (=-1 in C), and although ctrl + z *should* work, it didn't. Not sure why. */
	{
		putchar(c);
		c = getchar();
	}
	printf("\nHope I didn't annoy you by being a copy-cat...");
}