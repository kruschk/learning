#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define A 445
#define C 700001
#define M 2097152
#define INFINITY INT_MAX

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

enum visit {UNVISITED, VISITED};

/* data structure for implementing Dijkstra's algorithm */
struct dijkstra {
	unsigned int num_nodes;
	unsigned int num_unvisited;
	struct {
		enum visit visited;
		int distance;
	} *nodes;
};

/* dijkstra_init: initialize the dijkstra structure using information from the
 * graph so it may be used with the shortest paths algorithm */
void dijkstra_init(struct dijkstra *dijkstra, struct matrix *graph) {
	dijkstra->num_nodes = graph->height;
	dijkstra->num_unvisited = graph->height;
	dijkstra->nodes = malloc(dijkstra->num_nodes*sizeof *dijkstra->nodes);
}

/* dijkstra_clear: dijkstra structure elements to zero and free allocated
 * memory */
void dijkstra_clear(struct dijkstra *dijkstra) {
	dijkstra->num_nodes = 0;
	dijkstra->num_unvisited = 0;
	free(dijkstra->nodes);
	return;
}

/* dijkstra_shortest_paths: a (probably terrible) implementation of Dijkstra's
 * shortest paths algorithm */
void dijkstra_shortest_paths(struct dijkstra *dijkstra,
		struct matrix *graph, unsigned int current_node) {
	unsigned int i, j;
	/* mark all nodes as unvisited and initialize distances to "infinity" */
	for (i = 0; i < dijkstra->num_nodes; i++) {
		dijkstra->nodes[i].visited = UNVISITED;
		dijkstra->nodes[i].distance = INFINITY;
	}
	/* the current node has a distance from itself of 0 */
	dijkstra->nodes[current_node].distance = 0;
	/* determine the shortest path for each unvisited node */
	while (dijkstra->num_unvisited > 0) {
		int min = INFINITY;
		/* check each node that the current node points to, and if it has a
		 * nonzero edgeweight (indicating a path) and is also unvisited, then
		 * we compute a tentative distance for it */
		for (j = 0; j < dijkstra->num_nodes; j++) {
			if (graph->elements[OFFSET((*graph), current_node, j)] != 0
					&& dijkstra->nodes[j].visited == UNVISITED) {
				/* if the tentative distance is less than the currently stored
				 * shortest distance between the initial node and the current
				 * node, then we set the shortest distance to the tentative
				 * distance */
				int tentative_distance = dijkstra->nodes[current_node].distance
					+ graph->elements[OFFSET((*graph), current_node, j)];
				if (tentative_distance < dijkstra->nodes[j].distance) {
					dijkstra->nodes[j].distance = tentative_distance;
				}
			}
		}
		/* mark the current node as visited and decrement the count of
		 * unvisited nodes */
		dijkstra->nodes[current_node].visited = VISITED;
		dijkstra->num_unvisited--;
		/* select the unvisited node with the smallest tentative distance and
		 * set it as the current node */
		for (i = 0; i < dijkstra->num_nodes; i++) {
			if (dijkstra->nodes[i].visited == UNVISITED
					&& dijkstra->nodes[i].distance < min) {
				min = dijkstra->nodes[i].distance;
				current_node = i;
			}
		}
		/* If the smallest distance among the unvisited nodes is infinity,
		 * stop. This indicates there is no connection between the initial node
		 * and the remaining unvisited nodes. */
		if (min == INFINITY) {
			break;
		}
	}
	return;
}

/* print_dijkstra: print the distances in the dijkstra structure */
void print_dijkstra(struct dijkstra *dijkstra) {
	unsigned int i;
	for (i = 0; i < dijkstra->num_nodes; i++) {
		printf((i == dijkstra->num_nodes - 1) ? "%d\n" : "%d ",
				dijkstra->nodes[i].distance);
	}
	return;
}

int main(void) {
	struct matrix graph;
	unsigned int number_of_vertices, seed, initial_node;
	struct dijkstra dijkstra;
	/* get the number of vertices, initial seed value, and initial node */
	if (3 != scanf("%u %u %u\n", &number_of_vertices, &seed, &initial_node)) {
		fprintf(stderr, "error reading number of vertices, seed value, or "
				"initial node\n");
		exit(EXIT_FAILURE);
	}
	/* populate the graph with edge weights in the appropriate locations and
	 * print it for our viewing pleasure */
	matrix_init(&graph, number_of_vertices, number_of_vertices);
	generate_graph(&graph, number_of_vertices, seed);
	/*print_matrix(&graph);*/
	/* use Dijkstra's algorithm to compute the shortest paths */
	dijkstra_init(&dijkstra, &graph);
	dijkstra_shortest_paths(&dijkstra, &graph, initial_node - 1);
	print_dijkstra(&dijkstra);
	/* clean up */
	matrix_clear(&graph);
	dijkstra_clear(&dijkstra);
	return EXIT_SUCCESS;
}
