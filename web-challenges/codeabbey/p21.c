#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_NUM 20

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	/* can keep track of [1, 20]. 1 will be stored at index 1, 2 at index 1,
	 * ..., and 20 at index 19. */
	unsigned count[MAX_NUM] = {0}, max, next_num;
	size_t n_values, i;
	/* determine number of values and max number: */
	fgets(input, MAX_LINE, stdin);
	n_values = strtoul(input, &input_position, 10);
	max = strtoul(input_position, NULL, 10);
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* loop through each test case */
	for (i = 0; i < n_values; i++) {
		/* gather next line into input */
		next_num = strtoul(input_position, &input_position, 10);
		/* next num count is stored at index next_num-1 */
		count[next_num-1]++;
	}
	/* print results */
	for (i = 0; i < max; i++) {
		printf((i == max - 1) ? "%u\n" : "%u ", count[i]);
	}
	return 0;
}
