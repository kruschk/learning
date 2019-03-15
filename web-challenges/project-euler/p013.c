#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY_LENGTH 10000
#define MAXDIGITS 9
#define OVERFLOW 1000000000 
#define BASE 10

typedef unsigned int Num_chunk;

size_t bigsum(char result[], const size_t lim, const char a[], const char b[]);
size_t trim_trailing_zeroes(char s[]);
int reverse_str(char s[]);
Num_chunk determine_carry(Num_chunk *sum);
Num_chunk n_digits_to_int(size_t n, const char *base_p, char **current_p);
size_t int_to_str(Num_chunk num, char result[], size_t start_pos);
void remove_trailing_newline(char s[]);

int main(int argc, char *argv[]) {
	unsigned int len = 0;
	if (argc == 2) {
		FILE *fp = fopen(argv[1], "r");

		size_t count = 0;
		char temp[MAX_ARRAY_LENGTH];      /* stores the result of bigsum */
		char sum[MAX_ARRAY_LENGTH] = "0"; /* running sum, initialized 0 */
		char next[MAX_ARRAY_LENGTH];      /* next number */

		if (fp == NULL) {
			fprintf(stderr, "error opening %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}

		while (fgets(next, MAX_ARRAY_LENGTH, fp) != NULL) {
			remove_trailing_newline(next);
			/* take the sum of the two numbers */
			bigsum(temp, MAX_ARRAY_LENGTH, sum, next);
			count++;
			/*printf("temp: %s\tsum: %s\tnext: %s\tcount: %lu\n", temp, sum, next, count);*/
			/* copy the result of bigsum to sum */
			strcpy(sum, temp);
		}

		fclose(fp);

		printf("sum: %s, count: %lu\n", sum, count);
	}
	else if (argc == 3) {
		char result[MAX_ARRAY_LENGTH] = {'\0'};
		size_t i;
		len = (strlen(argv[1]) > strlen(argv[2])) ? strlen(argv[1]) :
			strlen(argv[2]);
		printf(" %*s\n+%*s\n", len, argv[1], len, argv[2]);
		bigsum(result, MAX_ARRAY_LENGTH, argv[1], argv[2]);
		for (i = 0; i < len+1; i++) {
			putchar('-');
		}
		printf("\n%*s\n", len+1, result);
	}
	else {
		printf("usage: %s [num1 num2]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return 0;
}

/* remove_trailing_newline: remove the trailing newline from the string
 * returned by fgets */
void remove_trailing_newline(char s[]) {
	size_t len = strlen(s);
	len--;
	if (s[len] == '\n') {
		s[len] = '\0';
	}
}

/* bigsum: take the sum of two large numbers a and b and store it in result;
 * return the length of result */
size_t bigsum(char result[], const size_t lim, const char a[], const char b[]) {
	char *a_pos = (char *)a + strlen(a)-1;
	char *b_pos = (char *)b + strlen(b)-1;
	size_t i = 0;
	Num_chunk carry = 0;
	Num_chunk numa = 0;
	Num_chunk numb = 0;
	Num_chunk sum = 0;

	/* Get two numbers of MAXDIGITS digits, add them (and carry, if set),
	 * determine if another carry is necessary, then append the result to the
	 * append string. Only go to lim-1 so there is room for a potential final
	 * carry and '\0'. */
	while (i < lim-1 && a_pos >= a && b_pos >= b) {
		numa = n_digits_to_int(MAXDIGITS, a, &a_pos);
		numb = n_digits_to_int(MAXDIGITS, b, &b_pos);
		sum = numa + numb + carry;
		carry = determine_carry(&sum);
		i = int_to_str(sum, result, i);
	}
	/* similar to first block, but if there are no characters from b left */
	while (i < lim-1 && a_pos >= a) {
		numa = n_digits_to_int(MAXDIGITS, a, &a_pos);
		sum = numa + carry;
		carry = determine_carry(&sum);
		i = int_to_str(sum, result, i);
	}
	/* similar to first block, but if there are no characters from a left */
	while (i < lim-1 && b_pos >= b) {
		numb = n_digits_to_int(MAXDIGITS, b, &b_pos);
		sum = numb + carry;
		carry = determine_carry(&sum);
		i = int_to_str(sum, result, i);
	}
	/* don't forget the carry */
	if (i < lim-1 && carry) {
		result[i++] = '1';
	}

	/* null-terminate the string */
	result[i] = '\0';

	/* trim the trailing zeroes (which become leading zeroes once the string is
	 * reversed) */
	i = trim_trailing_zeroes(result);

	/* reverse the string */
	reverse_str(result);

	return i;
}

/* trim_trailing_zeroes: trim the trailing '0' characters from a string */
size_t trim_trailing_zeroes(char s[]) {
	size_t i = strlen(s) - 1;
	while (s[i] == '0' && i != 0) {
		i--;
	}
	s[++i] = '\0';
	return i;
}

/* reverse_str: reverse a string in-place */
int reverse_str(char s[]) {
	size_t i;
	size_t j = strlen(s) - 1;
	for (i = 0; i < j; i++, j--) {
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
	return 0;
}

/* integer_power: return base^exponent; positive, integer arguments only */
Num_chunk integer_power(Num_chunk base, size_t exponent) {
	size_t i;
	Num_chunk result = 1;
	for (i = 0; i < exponent; i++) {
		result *= base;
	}
	return result;
}

/* n_digits_to_int: get n digits from base_p using the pointer positioned at
 * current_p */
Num_chunk n_digits_to_int(size_t n, const char *base_p, char **current_p) {
	size_t i;
	Num_chunk num = 0;
	for (i = 0; i < n; i++) {
		if (*current_p >= base_p) {
			num += (**current_p - '0')*integer_power(BASE, i);
			(*current_p)--;
		}
	}
	return num;
}

/* determine_carry: check if a carry needs to be performed, given the sum */
Num_chunk determine_carry(Num_chunk *sum) {
	if (*sum >= OVERFLOW) {
		*sum -= OVERFLOW;
		return 1;
	}
	else {
		return 0;
	}
}

/* int_to_str: given a num, converts it to characters in result starting
 * from pos in result, returns the next position in the result */
size_t int_to_str(Num_chunk num, char result[], size_t pos) {
	size_t i = 0;
	/* convert integers to string and append to result */
	while (num != 0) {
		result[pos] = (num % BASE) + '0';
		num /= BASE;
		pos++;
		i++;
	}
	/* have to pad with zeros if num didn't have MAXDIGITS digits, otherwise
	 * some zeros can be wrongly skipped */
	while (i < MAXDIGITS) {
		result[pos] = '0';
		pos++;
		i++;
	}
	return pos;
}
