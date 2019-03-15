#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_algebra.h"
#include "custom_round.h"
#define MAX_NAME 128
#define DIMENSIONS 2
#define MY_PI acos(-1)

/* star structure, containing the name and coordinates of a star */
struct star {
	char name[MAX_NAME];
	double x;
	double y;
};

/* star_compare: comparison function for sorting stars in the order requested
 * by the problem with qsort */
int star_compare(const void *key, const void *datum) {
	struct star *key_star = (struct star *)key;
	struct star *datum_star = (struct star *)datum;
	if (key_star->y != datum_star->y) {
		return (int)(key_star->y - datum_star->y);
	}
	else {
		return (int)(key_star->x - datum_star->x);
	}
}

int main(void) {
	unsigned int num_stars, i;
	double rotation_angle_deg, rotation_angle_rad;
	struct star *star_array;
	Matrix rotation_matrix, initial_coords, transformed_coords;
	/* initialize matrices */
	matrix_init(&rotation_matrix, DIMENSIONS, DIMENSIONS);
	matrix_init(&initial_coords, DIMENSIONS, 1);
	matrix_init(&transformed_coords, DIMENSIONS, 1);
	/* get the number of stars and the rotation angle (in degrees) */
	if (2 != scanf("%u %lf\n", &num_stars, &rotation_angle_deg)) {
		fprintf(stderr, "error reading number of stars or rotation angle on "
				"line 1\n");
		exit(EXIT_FAILURE);
	}
	/* allocate memory for the star array */
	star_array = malloc(num_stars*sizeof *star_array);
	/* build the 2-D rotation matrix */
	rotation_angle_rad = rotation_angle_deg*MY_PI/180.0;
	rotation_matrix.elements[OFFSET(rotation_matrix, 0, 0)]
		= cos(rotation_angle_rad);
	rotation_matrix.elements[OFFSET(rotation_matrix, 0, 1)]
		= -sin(rotation_angle_rad);
	rotation_matrix.elements[OFFSET(rotation_matrix, 1, 0)]
		= sin(rotation_angle_rad);
	rotation_matrix.elements[OFFSET(rotation_matrix, 1, 1)]
		= cos(rotation_angle_rad);
	/* get the name and initial coordinates of each star, then compute the
	 * coordinates after the rotation */
	for (i = 0; i < num_stars; i++) {
		char name[MAX_NAME];
		double x, y;
		/* get the name and initial coordinates of each star */
		if (3 != scanf("%127s %lf %lf\n", name, &x, &y)) {
			fprintf(stderr, "error reading star name or coordinates on line "
					"%u\n", i + 2);
			exit(EXIT_FAILURE);
		}
		/* copy the name to the appropriate space in the star_array */
		strncpy(star_array[i].name, name, MAX_NAME-1);
		/* add the initial coordinates to the initial_coords vector */
		initial_coords.elements[OFFSET(initial_coords, 0, 0)] = x;
		initial_coords.elements[OFFSET(initial_coords, 1, 0)] = y;
		/* the transformed coordinates are computed by right-multiplying the
		 * rotation matrix by the initial coords */
		matrix_multiply(&transformed_coords, &rotation_matrix,
				&initial_coords);
		/* assign the transformed coordinates to the appropriate place in the
		 * star array */
		star_array[i].x =
			transformed_coords.elements[OFFSET(transformed_coords, 0, 0)];
		star_array[i].y =
			transformed_coords.elements[OFFSET(transformed_coords, 1, 0)];
	}
	/* sort the stars according to our comparison function */
	qsort(star_array, num_stars, sizeof *star_array, star_compare);
	/* print the results */
	for (i = 0; i < num_stars; i++) {
		printf((i == num_stars - 1) ? "%s\n" : "%s ", star_array[i].name);
	}
	/* clean up */
	matrix_clear(&rotation_matrix);
	matrix_clear(&initial_coords);
	matrix_clear(&transformed_coords);
	free(star_array);
	return 0;
}
