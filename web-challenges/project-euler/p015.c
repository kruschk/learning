#include <stdio.h>

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

struct lattice_node {
	struct lattice_node *right; /* NULL if at edge of grid */
	struct lattice_node *down; /* NULL if at edge of grid */
};

struct lattice_node node_array[GRID_WIDTH+1][GRID_HEIGHT+1];

/* construct_lattice: construct the lattice given the grid dimensions, note:
 * a lattice of size width*height will have (width+1)*(height+1) nodes. */
int construct_lattice(const size_t width, const size_t height) {
	size_t i, j;
	for (i = 0; i <= height; i++) {
		for (j = 0; j <= width; j++) {
			if (!(i == height) && !(j == height)) {
				node_array[i][j].right = &node_array[i][j+1];
				node_array[i][j].down = &node_array[i+1][j];
			}
			else if ((i == height) && (j == height)) {
				node_array[i][j].right = NULL;
				node_array[i][j].down = NULL;
			}
			else if (i == height) {
				node_array[i][j].right = &node_array[i][j+1];
				node_array[i][j].down = NULL;
			}
			else if (j == width) {
				node_array[i][j].right = NULL;
				node_array[i][j].down = &node_array[i+1][j];
			}
			else {
				printf("this should be impossible\n");
			}
		}
	}

	return 0;
}

/* traverse_lattice: return 1 if a path was found, 0 if not. A path is found
 * when the node at node_array[width+1][height+1] is reached */
size_t traverse_lattice(const struct lattice_node *start, const struct lattice_node *goal) {
	static size_t npaths = 0;
	if (start->right == goal || start->down == goal) {
		npaths++;
		return npaths;
	}

	/* go right as far as possible first (using recursion) */
	if (start->right != NULL) {
		traverse_lattice(start->right, goal);
	}

	if (start->down != NULL) {
		traverse_lattice(start->down, goal);
	}

	return npaths;
}

/* lattice_path_series: returns f(n) = f(n-1)*((4n-2)/n) */
size_t lattice_path_series(const size_t n) {
	size_t i;
	size_t last = 2;
	size_t new;
	for (i = 2; i <= n; i++) {
		new = last*((4.0*i-2.0)/i);
		last = new;
	}
	return new;
}

/* lattice_path_series_recursive: returns f(n) = f(n-1)*((4n-2)/n) */
size_t lattice_path_series_recursive(const size_t n) {
	if (n == 1) {
		return 2;
	}
	else {
		return lattice_path_series_recursive(n-1)*(4.0*n-2.0)/n;
	}
}

/* lattice_path_series_tail_recursive_helper: returns f(n) = f(n-1)*((4n-2)/n) */
size_t lattice_path_series_tail_recursive_helper(const size_t n, size_t i,
		size_t result) {
	if (i == n) {
		return result;
	}
	else {
		i++;
		result *= ((4.0*i-2.0)/i);
		return lattice_path_series_tail_recursive_helper(n, i, result);
	}
}

/* lattice_path_series_tail_recursive: returns f(n) = f(n-1)*((4n-2)/n) */
size_t lattice_path_series_tail_recursive(const size_t n) {
	/* the recursive formula is only valid for n>=2; the result is 6 when n=2 */
	return lattice_path_series_tail_recursive_helper(n, 2, 6);
}

int main(void) {
	size_t result = 0;
	/*
	size_t npaths = 0;
	construct_lattice(GRID_WIDTH, GRID_HEIGHT);
	npaths = traverse_lattice(&node_array[0][0],
			&node_array[GRID_WIDTH][GRID_HEIGHT]);
	printf("npaths: %lu\n", npaths);
	*/

	/* Using the above code, found that the series was 2, 6, 20, 70, 252, 924,
	 * 3432, 12870, 48620, 184756, ...  for n = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	 * .... Taking f(n)/f(n-1), for each n, one can deduce that this is a
	 * geometric series since each ratio is rational. Then, writing out the
	 * terms in a table (n | f(n) | f(n)/f(n-1)) and expanding them as mixed
	 * fractions, it becomes apparent that f(n)/f(n-1) = 3+(n-2)/n, or
	 * f(n) = f(n-1)*((4n-2)/n). */
	result = lattice_path_series(20);
	printf("iterative result: %lu\n", result);

	result = lattice_path_series_recursive(20);
	printf("recursive result: %lu\n", result);

	result = lattice_path_series_tail_recursive(20);
	printf("tail recursive result: %lu\n", result);

	/* Note: it turns out this is related to Pascal's triangle and the N choose
	 * R formula/binomial coefficient formula. */
	return 0;
}
