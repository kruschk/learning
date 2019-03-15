#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char line[MAX_LINE], *line_p;
	size_t n_cases, i, shift;
	/* get number of cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, &line_p, 10);
	/* get the shift value, note that 'Z' - 'A' + 1 = 90 - 65 + 1 = 26 */
	shift = ('Z' - 'A' + 1) - strtoul(line_p, NULL, 10);
	/* print the decoded message for each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		char encoded, decoded;
		/* get the next line */
		fgets(line, MAX_LINE, stdin);
		line_p = line;
		/* decode the message */
		while ((encoded = *(line_p++)) != '.') {
			/* don't decode spaces */
			if (isspace(encoded)) {
				putchar(encoded);
			}
			else {
				/* ASCII 'A' is 65, 'Z' is 90, all other capital letters are in
				 * between. This subtracts 'A' to put the number in the range
				 * [0, 25] (enough for all 26 letters). Then, it shifts it so
				 * it's in the range [shift, 25 + shift]. Now it takes this
				 * number modulo 90 - 65 + 1 = 26 to put it back in the range
				 * [0, 25]. Finally, it adds 65 again so we're in the range
				 * [65, 90], but with the number shifted by the appropriate
				 * amount. */ 
				decoded = (encoded - 'A' + shift) % ('Z' - 'A' + 1) + 'A';
				/* print the character */
				putchar(decoded);
			}
		}
		/* end a message with a '.' and put a newline if appropriate */;
		printf((i == n_cases - 1) ? ".\n" : ". ");
	}
	return 0;
}
