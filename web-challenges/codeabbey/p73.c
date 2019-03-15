#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MOVES 128

/* allowable moves */
enum moves {RIGHT = 'A', UP_RIGHT = 'B', UP_LEFT = 'C', LEFT = 'D',
	DOWN_LEFT = 'E', DOWN_RIGHT = 'F'};

/* describes position of a point on the map */
struct coords {
	double x;
	double y;
};

/* update_position: update the position of coords based on a certain move */
void update_position(struct coords *coords, enum moves move) {
	const double x_component = 0.5; /* moving left or right */
	const double y_component = sqrt(3)/2; /* angle is 60 deg */
	switch (toupper(move)) {
		case RIGHT:
			coords->x += 1.0;
			break;
		case UP_RIGHT:
			coords->x += x_component;
			coords->y += y_component;
			break;
		case UP_LEFT:
			coords->x -= x_component;
			coords->y += y_component;
			break;
		case LEFT:
			coords->x -= 1.0;
			break;
		case DOWN_LEFT:
			coords->x -= x_component;
			coords->y -= y_component;
			break;
		case DOWN_RIGHT:
			coords->x += x_component;
			coords->y -= y_component;
			break;
		default:
			fprintf(stderr, "unrecognized move\n");
			break;
	}
	return;
}

/* compute_distance: return the distance between any two points */
double compute_distance(const struct coords *origin, const struct coords *coords) {
	return sqrt(pow(coords->y - origin->y, 2) + pow(coords->x - origin->x, 2));
}

int main(void) {
	/* get the number of cases from input */
	int scan_status = 0;
	unsigned int cases, i;
	scan_status = scanf("%u\n", &cases);
	if (scan_status != 1) {
		fprintf(stderr, "failed to get the number of cases from input\n");
		exit(EXIT_FAILURE);
	}
	/* compute the distance moved from the origin in each case */
	for (i = 0; i < cases; i++) {
		char *status_p;
		char moves[MAX_MOVES];
		unsigned int num_moves, j;
		struct coords player_pos = {0, 0};
		const struct coords origin = {0, 0};
		double distance = 0;
		/* get the moves from input */
		status_p = fgets(moves, MAX_MOVES, stdin);
		/* fgets returned NULL and EOF is NOT set is an error */
		if (status_p == NULL && feof(stdin) != 0) {
			fprintf(stderr, "failed to get set of moves #%u from input\n",
					i + 1);
			exit(EXIT_FAILURE);
		}
		/* compute the length of the string */
		num_moves = strlen(moves);
		/* ignore newline, if present */
		if (moves[num_moves - 1] == '\n') {
			moves[num_moves - 1] = '\0';
			num_moves--;
		}
		/* make the moves */
		for (j = 0; j < num_moves; j++) {
			update_position(&player_pos, moves[j]);
		}
		/* compute the distance from the origin */
		distance = compute_distance(&origin, &player_pos);
		/* print the result */
		printf((i == cases - 1) ? "%.8f\n" : "%.8f ", distance);
	}
	return 0;
}
