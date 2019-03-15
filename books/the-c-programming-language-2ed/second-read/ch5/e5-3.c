#include <stdio.h>
#define MAX_STR 1024

void strcat2(char s[], char t[]);

int main(void) {
	char s[MAX_STR] = "test";
	char t[] = " string";
	printf("s: \"%s\"\n", s);
	printf("t: \"%s\"\n", t);
	strcat2(s, t);
	printf("strcat(s, t): %s\n", s);
	return 0;
}

/* strcat: concatenate t to end of s; s must be big enough */
void strcat2(char *s, char *t) {
	/* find where s ends */
	while (*s != '\0') {
		s++;
	}
	/* copy t to s, starting from this point */
	while ((*s = *t) != '\0') {
		s++;
		t++;
	}
}
