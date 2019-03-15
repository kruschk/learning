#include <stdio.h>

short main(void) {
	char c = ' ';
	
	while (c < 127) {
		putchar(c++);
	}
	
	putchar('\n');
	
	for (char printable = 32; printable < 127; printable++) {
		putchar(printable);
	}
	
	return 0;
}