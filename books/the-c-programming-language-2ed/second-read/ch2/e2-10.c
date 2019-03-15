#include <stdio.h>

int lower(int c) ;

int main(void) {
	char str[] = "ThiS is A saMPLe strinG.\n";
	int i;

	printf("%s", str);

	for (i = 0; str[i] != '\0'; ++i) {
		str[i] = lower(str[i]);
	}

	printf("%s", str);

	return 0;
}

int lower(int c) {
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
	/* equivalent: */
	/*
	if (c >= 'A' && c <= 'Z') {
		return c + 'a' - 'A';
	}
	else {
		return c;
	}
	*/
}
