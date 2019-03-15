#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_PEOPLE 1024
#define ALIVE 1
#define DEAD 0

/* count_alive: count the number of people who are alive in the array */
size_t count_alive(char *array, size_t n) {
	size_t count = 0;
	size_t i = 0;
	for (i = 0; i < n; i++) {
		if (array[i] == ALIVE) {
			count++;
		}
	}
	return count;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_people, i, step;
	char array[MAX_PEOPLE];
	/* get number of people and the step size */
	fgets(input, MAX_LINE, stdin);
	n_people = strtoul(input, &input_position, 10);
	step = strtoul(input_position, NULL, 10);
	/* populate the array with initial state of the people */
	for (i = 0; i < n_people; i++) {
		array[i] = ALIVE;
	}
	/* kill the person at every step'th position, skipping over dead people and
	 * wrapping the index counter with modulus */
	i = 0;
	while (count_alive(array, n_people) > 1) {
		/* search for the step'th person in the list who is alive */
		size_t j = step - 1;
		while (j > 0) {
			if (array[i] == ALIVE) {
				j--;
			}
			i++;
			i %= n_people;
		}
		/* kill the next person in the list who is alive (i.e. skip over any
		 * dead folks) */
		while (array[i] == DEAD) {
			i++;
			i %= n_people;
		}
		array[i] = DEAD;
	}
	/* find the guy who is alive */
	for (i = 0; array[i] == DEAD; i++) {
		;
	}
	/* print the 1-indexed safe position */
	printf("%lu\n", ++i);
	return 0;
}
