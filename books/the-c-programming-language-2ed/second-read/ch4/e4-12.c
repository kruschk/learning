#include <stdio.h>
#include <limits.h>
#define MAX_DIGITS 1024

int itoa(int n, char s[]);
void recurse(int n, char s[], int *pos);

int main(void) {
	char s[MAX_DIGITS];
	int number = INT_MIN;
	itoa(number, s);
	printf("INT_MIN: %s\n", s);

	number = INT_MAX;
	itoa(number, s);
	printf("INT_MAX: %s\n", s);
	return 0;
}

/* itoa: convert n to string */
int itoa(int n, char s[]){
	int pos = 0;
	if (n < 0) {
		s[pos] = '-';
		pos++;
	}
	recurse(n, s, &pos);
	s[pos] = '\0';

	return 0;
}

/* recurse: perform the recursive portion of itoa */
void recurse(int n, char s[], int *pos) {
	int current_num = n / 10;
	if (current_num) {
		recurse(current_num, s, pos);
	}
	s[*pos] = (n < 0) ? (-(n % 10) + '0') : (n % 10 + '0');
	(*pos)++;
}
