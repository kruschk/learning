#include <stdio.h>
#include <stdlib.h>
#define A 445
#define C 700001
#define M 2097152

/* compute the offset of a 2-D malloc'd array */
#define OFFSET(matrix, r, c) ((r)*matrix.width + (c))

/* matrix structure with integer elements */
struct matrix {
	unsigned int height;
	unsigned int width;
	int *elements;
};

/* lcg: a linear congruential generator; generates a pseudorandom number given
 * seed as input */
unsigned int lcg(const unsigned int seed) {
	return (A*seed + C)%M;
}

/* print_matrix: print a matrix, with the 1-indexed columns in the first row
 * and 1-indexed rows in the first column */
void print_matrix(struct matrix *matrix) {
	unsigned int i, j;
	printf("   ");
	for (j = 0; j < matrix->width; j++) {
		printf("%2u ", j + 1);
	}
	putchar('\n');
	for (i = 0; i < matrix->height; i++) {
		printf("%2u ", i + 1);
		for (j = 0; j < matrix->width; j++) {
			printf((j == matrix->width - 1) ? "%2d\n" : "%2d ",
					matrix->elements[OFFSET((*matrix), i, j)]);
		}
	}
}

/* matrix_init: initialize a matrix with the given height and width dimensions,
 * and set its elements to zero */
void matrix_init(struct matrix *matrix, unsigned int height, unsigned int width) {
	unsigned int i;
	matrix->height = height;
	matrix->width = width;
	matrix->elements =
		malloc(matrix->height*matrix->width*sizeof *matrix->elements);
	for (i = 0; i < matrix->height; i++) {
		unsigned int j;
		for (j = 0; j < matrix->width; j++) {
			matrix->elements[OFFSET((*matrix), i, j)] = 0;
		}
	}
	return;
}

/* matrix_clear: set matrix elements to zero and free allocated memory */
void matrix_clear(struct matrix *matrix) {
	matrix->height = 0;
	matrix->width = 0;
	free(matrix->elements);
	return;
}

/* generate_graph: generate a graph containing pseudorandom connections and
 * weight values */
void generate_graph(struct matrix *graph, unsigned int number_of_vertices,
		unsigned int seed) {
	unsigned int i;
	for (i = 0; i < graph->height; i++) {
		unsigned int value1, distance1, value2, distance2;
		seed = lcg(seed);
		value1 = seed%number_of_vertices;
		seed = lcg(seed);
		if (i != value1 && 0 == graph->elements[OFFSET((*graph), i, value1)]
				&& 0 == graph->elements[OFFSET((*graph), value1, i)]) {
			distance1 = seed%number_of_vertices;
			graph->elements[OFFSET((*graph), i, value1)] = distance1 + 1;
			graph->elements[OFFSET((*graph), value1, i)] = distance1 + 1;
		}
		seed = lcg(seed);
		value2 = seed%number_of_vertices;
		seed = lcg(seed);
		if (i != value2 &&  0 == graph->elements[OFFSET((*graph), i, value2)]
				&& 0 == graph->elements[OFFSET((*graph), value2, i)]) {
			distance2 = seed%number_of_vertices;
			graph->elements[OFFSET((*graph), i, value2)] = distance2 + 1;
			graph->elements[OFFSET((*graph), value2, i)] = distance2 + 1;
		}
	}
	return;
}

/* print_sums_of_rows: print the sum of each row of the graph, separated by
 * spaces */
void print_sums_of_rows(struct matrix *graph) {
	unsigned int i;
	for (i = 0; i < graph->height; i++) {
		unsigned int j;
		int sum = 0;
		for (j = 0; j < graph->width; j++) {
			sum += graph->elements[OFFSET((*graph), i, j)];
		}
		printf((i == graph->height - 1) ? "%d\n" : "%d ", sum);
	}
}

int main(void) {
	struct matrix graph;
	unsigned int number_of_vertices, seed;
	/* get the number of vertices and the initial seed value */
	if (2 != scanf("%u %u\n", &number_of_vertices, &seed)) {
		fprintf(stderr, "error reading number of vertices or seed value\n");
		exit(EXIT_FAILURE);
	}
	/* initialize the graph */
	matrix_init(&graph, number_of_vertices, number_of_vertices);
	/* populate the graph with edge weights in the appropriate locations */
	generate_graph(&graph, number_of_vertices, seed);
	/* print the matrix for our viewing pleasure */
	print_matrix(&graph);
	/* print the desired results */
	print_sums_of_rows(&graph);
	/* free the matrix */
	matrix_clear(&graph);
	return EXIT_SUCCESS;
}
