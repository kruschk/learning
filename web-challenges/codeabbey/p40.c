#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 64
#define MAX_ROWS 32
#define MAX_COLS 32
#define START '@'
#define END '$'
#define SAFE '+'
#define PIT 'X'

/* define a struct for each point on the map */
struct map_point {
	char terrain; /* terrain at the point */
	unsigned int n_paths; /* number of paths from the point */
};

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_rows, n_cols, i, j;
	struct map_point map[MAX_ROWS][MAX_COLS];
	/* get the number of rows and columns */
	fgets(input, MAX_LINE, stdin);
	n_rows = strtoul(input, &input_position, 10);
	n_cols = strtoul(input_position, NULL, 10);
	/* build the map terrain and print it as we go */
	for (i = 0; i < n_rows; i++) {
		fgets(input, MAX_LINE, stdin);
		input_position = input;
		for (j = 0; j < n_cols; j++) {
			/* skip whitespace */
			while (isspace(*input_position)) {
				input_position++;
			}
			/* assign the character to the terrain at the input position */
			map[i][j].terrain = *input_position;
			input_position++;
			/* print */
			putchar(map[i][j].terrain);
		}
		putchar('\n');
	}
	/* we assign the destination to have 1 path from it to the destination */
	map[n_rows-1][n_cols-1].n_paths = 1;
	/* populate bottom row */
	for (j = n_cols - 1; j != 0;) {
		j--;
		/* if there's a pit, set it to have 0 paths to the destination */
		if (map[n_rows-1][j].terrain == PIT) {
			map[n_rows-1][j].n_paths = 0;
		}
		/* otherwise, set the point to have the same number of paths as the
		 * point to the right of it */
		else {
			map[n_rows-1][j].n_paths = map[n_rows-1][j+1].n_paths;
		}
	}
	/* populate rightmost column */
	for (i = n_rows - 1; i != 0;) {
		i--;
		/* if there's a pit, set it to have 0 paths to the destination */
		if (map[i][n_cols-1].terrain == PIT) {
			map[i][n_cols-1].n_paths = 0;
		}
		/* otherwise, set the point to have the same number of paths as the
		 * point below it */
		else {
			map[i][n_cols-1].n_paths = map[i+1][n_cols-1].n_paths;
		}
	}
	/* calculate the number of paths from each position, building up toward the
	 * starting position */
	for (i = n_rows - 1; i != 0;) {
		i--;
		for (j = n_cols - 1; j != 0;) {
			j--;
			/* if the point is a pit, set it to 0 */
			if (map[i][j].terrain == PIT) {
				map[i][j].n_paths = 0;
			}
			/* the number of paths from this point is equal to the number of
			 * paths from the point below it plus the number of paths from the
			 * point to the right */
			else {
				map[i][j].n_paths = map[i+1][j].n_paths + map[i][j+1].n_paths;
			}
		}
	}
	/* print the number of paths to the destination from each point on the
	 * map */
	for (i = 0; i < n_rows; i++) {
		for (j = 0; j < n_cols; j++) {
			printf("%10u ", map[i][j].n_paths);
		}
		putchar('\n');
	}
	/* print result */
	printf("Number of paths from start: %u\n", map[0][0].n_paths);
	return 0;
}
