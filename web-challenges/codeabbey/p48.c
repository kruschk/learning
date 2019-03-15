#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char line[MAX_LINE], *line_p;
	size_t n_cases, i;
	/* get number of cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* get the second line, which contains the test numbers */
	fgets(line, MAX_LINE, stdin);
	line_p = line;
	/* determine the number of iterations before the sequences decays to 1 for
	 * each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare/initialize variables */
		size_t num, count = 0;
		/* get the number */
		num = strtoul(line_p, &line_p, 10);
		/* count the number of iterations until the number becomes 1 */
		while (num != 1) {
			if (num % 2 == 0) {
				num /= 2;
			}
			else {
				num = 3*num + 1;
			}
			count++;
		}
		/* print result */
		printf((i == n_cases - 1) ? "%lu\n" : "%lu ", count);
	}
	return 0;
}
