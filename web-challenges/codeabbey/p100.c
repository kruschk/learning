#include <stdio.h>
#include <stdlib.h>
#define LANES 11
#define ROAD_LENGTH 34
#define PLAYER '@'
#define ROAD '-'
#define CAR '$'
#define CAR_NEXT_POSITION '+'
#define INITIAL_SPEED 5
#define INITIAL_SPACING 18

enum boolean {FALSE, TRUE};

void update_road(char road[][ROAD_LENGTH]) {
	unsigned int i, j;
	/* initial spacing and speed values */
	unsigned int spacing = INITIAL_SPACING;
	unsigned int speed = INITIAL_SPEED;
	for (i = 0; i < LANES; i++) {
		/* advance the cars so they are at their next positions */
		for (j = 0; j < ROAD_LENGTH; j++) {
			if (CAR == road[i][j]) {
				if (j >= speed) {
					road[i][j - speed] = CAR; /* add car at next position */
					/* draw the next position of the car we just drew, if
					 * there's room */
					if (j >= 2*speed) {
						road[i][j - 2*speed] = CAR_NEXT_POSITION;
					}
				}
				road[i][j] = ROAD; /* erase car at this position */
			}
		}
		/* find the last car */
		j = ROAD_LENGTH;
		while (j-- > 0) {
			if (CAR == road[i][j]) {
				/* draw the new last car and its next position */
				while ((j += spacing) < ROAD_LENGTH) {
					road[i][j] = CAR;
					if (j >= speed) {
						road[i][j - speed] = CAR_NEXT_POSITION;
					}
				}
				break;
			}
		}
		/* vehicle spacings and speeds increase with increasing lanes */
		spacing++;
		speed++;
	}
}

/* print the road */
void print_road(char road[][ROAD_LENGTH]) {
	unsigned int i, j;
	for (i = 0; i < LANES; i++) {
		for (j = 0; j < ROAD_LENGTH; j++) {
			printf((j == ROAD_LENGTH - 1) ? "%c" : "%c ", road[i][j]);
		}
		putchar('\n');
	}
	return;
}

int main(void) {
	char road[LANES][ROAD_LENGTH];
	unsigned int i, j, spacing, speed;
	/* initialize the board */
	for (i = 0; i < LANES; i++) {
		for (j = 0; j < ROAD_LENGTH; j++) {
			road[i][j] = ROAD;
		}
	}
	/* player at top-left */
	road[0][0] = PLAYER;
	/* get the first cars from input */
	spacing = INITIAL_SPACING;
	speed = INITIAL_SPEED;
	for (i = 0; i < LANES; i++) {
		unsigned int next_car;
		if (1 != scanf("%u ", &next_car)) {
			fprintf(stderr, "error reading car %u's position", i + 1);
			exit(EXIT_FAILURE);
		}
		else if (next_car < ROAD_LENGTH) {
			do {
				road[i][next_car] = CAR;
				if (next_car >= speed) {
					road[i][next_car - speed] = CAR_NEXT_POSITION;
				}
			}
			while ((next_car += spacing) < ROAD_LENGTH);
		}
		else {
			fprintf(stderr, "failed to place car %u on the board", i + 1);
			exit(EXIT_FAILURE);
		}
		spacing++;
		speed++;
	}
	print_road(road);
	putchar('\n');
	update_road(road);
	print_road(road);
	return 0;
}
