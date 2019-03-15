#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main(void) {
	char s[1024] = "this is a string ";
	char t[] = "tring ";

	printf("status: %d\n", strend(s, t));

	return 0;
}

/* strend: return 1 if string t occurs at the end of s, and 0 otherwise */
int strend(char *s, char *t) {
	/* method with indeces and array subscripting: */
	/*
	size_t i = strlen(s) - 1;
	size_t j = strlen(t) - 1;
	while (s[i] == t[j] && i != 0 && j != 0) {
		--i;
		--j;
	}
	if (s[i] == t[j] && j == 0) {
		return 1;
	}
	return 0;
	*/

	/* method using pointers */
	const char *s_base = s;
	const char *t_base = t;

	/* set s and t to point to the ends of their respective arrays */
	while (*s != '\0') {
		s++;
	}
	s--; /* point to the last non-'\0' char */
	while (*t != '\0') {
		t++;
	}
	t--;
	
	while ((*s == *t) && s != s_base && t != t_base) {
		--s;
		--t;
	}
	/* match */
	if ((*s == *t) && t == t_base) {
		return 1;
	}
	/* no match */
	else {
		return 0;
	}
}
