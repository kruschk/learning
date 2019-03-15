#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_STATES 64

/* print_states: print the states array */
void print_states(const char *states[], const size_t length) {
	char **p;
	for (p = (char **)states; (size_t)(p - (char **)states) < length; p++) {
		printf("%s", *p);
	}
	putchar('\n');
}

/* print_distances: print the distances matrix */
void print_distances(unsigned int dist[MAX_STATES][MAX_STATES], char *states[],
		const size_t vertices) {
	size_t i, j;
	printf("    ");
	for (i = 0; i < vertices; i++) {
		printf("%.3s ", states[i]);
	}
	putchar('\n');
	for (j = 0; j < vertices; j++) {
		printf("%.3s ", states[j]);
		for (i = 0; i < vertices; i++) {
			if (dist[j][i] == INT_MAX) {
				printf("INF ");
			}
			else {
				printf("%3u ", dist[j][i]);
			}
		}
		putchar('\n');
	}
}

/* strcmp_wrapper: wrapper for strcmp so that it works with qsort to sort an
 * array of strings alphabetically */
int strcmp_wrapper(const void *keyval, const void *datum) {
	/* in general, keyval and datum must be passed to the same type as base
	 * (the first argument to qsort), then dereferenced */
	const char *str1 = *(const char **)keyval;
	const char *str2 = *(const char **)datum;
	return strcmp(str1, str2);
}

enum boolean {FALSE, TRUE};

/* is_new_state: returns TRUE if the given state does not exist in the states
 * array, false otherwise */
enum boolean is_new_state(const char *states[], const char state[]) {
	size_t i;
	for (i = 0; i < MAX_STATES; i++) {
		if (states[i] != NULL) {
			if (strcmp(states[i], state) == 0) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

/* add_new_state: add a new state to the states array */
int add_new_state(char *states[], const char state[]) {
	size_t i;
	for (i = 0; i < MAX_STATES; i++) {
		if (states[i] == NULL) {
			states[i] = malloc((strlen(state) + 1)*(sizeof *state));
			strcpy(states[i], state);
			return i;
		}
	}
	return -1;
}

/* find_state: find the given state in states, and return its index */
int find_state(char *states[], const char state[]) {
	size_t i;
	for (i = 0; i < MAX_STATES; i++) {
		if (states[i] != NULL) {
			if (strcmp(states[i], state) == 0) {
				return i;
			}
		}
	}
	return -1;
}

/* delete_state: delete a given state form the states array */
int delete_state(char *states[], const char state[]) {
	int index = find_state(states, state);
	if (index != -1) {
		if (states[index] != NULL) {
			free(states[index]);
			states[index] = NULL;
			return index;
		}
		return -1;
	}
	return -2;
}

/* delete_all_states: delete all the states in the states array */
void delete_all_states(char *states[]) {
	size_t i;
	for (i = 0; i < MAX_STATES; i++) {
		if (states[i] != NULL) {
			free(states[i]);
			states[i] = NULL;
		}
	}
}

/* link_states: link two states in the distance matrix, assuming the edge
 * weight is 1 */
int link_states(unsigned int dist[MAX_STATES][MAX_STATES], char *states[],
		const char state1[], const char state2[]) {
	int index1 = find_state(states, state1);
	int index2 = find_state(states, state2);
	dist[index2][index1] = 1;
	dist[index1][index2] = 1;
	return 0;
}

/* floyd_warshall: implementation of the floyd_warshall algorithm. dist matrix
 * is assumed to be properly initialized */
void floyd_warshall(unsigned int dist[MAX_STATES][MAX_STATES], size_t vertices) {
	size_t i, j, k;
	for (k = 0; k < vertices; k++) {
		for (i = 0; i < vertices; i++) {
			for (j = 0; j < vertices; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					/* This condition has been added to defend against integer
					 * overflow, this works since dist contains unsigned ints.
					 * For signed, need to add additional conditions */
					if (!(dist[i][k] > INT_MAX - dist[k][j])) {
						/* sum won't overflow, go ahead */
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	}
}

int main(void) {
	char *states[MAX_STATES] = {NULL};
	char state1[MAX_LINE], state2[MAX_LINE];
	unsigned int dist[MAX_STATES][MAX_STATES];
	size_t n_edges, i, j, vertices = 0, n_shortest_distances;
	/* initialize states array */
	for (i = 0; i < MAX_STATES; i++) {
		states[i] = NULL;
	}
	/* initialize distance array to 0 on main diagonal and INT_MAX elsewhere */
	for (j = 0; j < MAX_STATES; j++) {
		for (i = 0; i < MAX_STATES; i++) {
			if (j == i) {
				dist[j][i] = 0;
			}
			else {
				dist[j][i] = INT_MAX;
			}
		}
	}
	/* populate the distance matrix and count the number of vertices */
	scanf("%lu\n", &n_edges);
	for (i = 0; i < n_edges; i++) {
		scanf("%s - %s\n", state1, state2);
		if (is_new_state((const char **)states, state1)) {
			add_new_state(states, state1);
			vertices++;
		}
		if (is_new_state((const char **)states, state2)) {
			add_new_state(states, state2);
			vertices++;
		}
		link_states(dist, states, state1, state2);
	}
	/* print the distance matrix */
	print_distances(dist, states, vertices);
	/* use the Floyd-Warshall algorithm to find the shortest distances between
	 * any two states */
	floyd_warshall(dist, vertices);
	/* print the distance matrix */
	print_distances(dist, states, vertices);
	/* get the number of shortest distances that we want to print from input */
	scanf("%lu\n", &n_shortest_distances);
	/* print them */
	for (i = 0; i < n_shortest_distances; i++) {
		int index1, index2;
		/* get the desired path */
		scanf("%s - %s\n", state1, state2);
		index1 = find_state(states, state1);
		index2 = find_state(states, state2);
		/* if both states were found, print them */
		if (index1 != -1 && index2 != -1) {
			printf((i == n_shortest_distances - 1) ? "%u\n" : "%u ", dist[index1][index2]);
		}
		else {
			perror("find_state: could not find requested state");
		}
	}
	/* free the malloc'ed memory */
	delete_all_states(states);
	return 0;
}
