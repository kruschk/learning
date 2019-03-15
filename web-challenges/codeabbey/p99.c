#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define CASES 3
#define RANGE_LENGTH 160 /* m */
#define BLOCK_WIDTH 4 /* m */
#define BLOCK_HEIGHT 4 /* m */
#define NUM_BLOCKS (RANGE_LENGTH/BLOCK_WIDTH)
#define SHOTS 3
#define PI acos(-1)

/* return the height of the projectile using the common kinematics formula */
float projectile_height(const float x, const float x_0, const float y_0,
		const float v_0, const float theta, const float a_y) {
	return y_0 + tan(theta)*(x - x_0)
		+ 0.5*a_y*(x - x_0)*(x - x_0)/(v_0*v_0*cos(theta)*cos(theta));
}

int main(void) {
	unsigned int i;
	/* in the terrain array, the array index is the x-coordinate */
	float terrain[RANGE_LENGTH];
	/* array to store the results */
	int results[CASES*SHOTS];
	for (i = 0; i < CASES; i++) {
		unsigned int j;
		/* build the terrain array */
		for (j = 0; j < NUM_BLOCKS; j++) {
			unsigned int k;
			/* get the height of the terrain (in block units) */
			float height;
			if (1 != scanf("%f ", &height)) {
				fprintf(stderr, "error reading terrain height\n");
				exit(EXIT_FAILURE);
			}
			/* build the terrain array */
			for (k = 0; k < BLOCK_WIDTH; k++) {
				terrain[j*BLOCK_WIDTH + k] = height*BLOCK_HEIGHT;
			}
		}
		/* find the horizontal distance at which the projectile strikes the
		 * terrain for each shot */
		for (j = 0; j < SHOTS; j++) {
			const float x_0 = 0.0; /* m */
			const float y_0 = 0.0; /* m */
			const float g = -9.81; /* m*s^-2 */
			const float step = 0.005; /* m */
			float x = x_0 + step; /* m */
			/* get the initial conditions of the projectile */
			float v_0, theta;
			if (2 != scanf("%f %f\n", &v_0, &theta)) {
				fprintf(stderr, "error reading initial conditions of projectile\n");
				exit(EXIT_FAILURE);
			}
			theta *= PI/180.0; /* convert theta to radians */
			/* Compute the height of the projectile as a function of x, and see
			 * if it's above the terrain (meaning no collision). If it is, step
			 * forward once and try again. */
			while (projectile_height(x, x_0, y_0, v_0, theta, g)
					> terrain[(int)(x - x_0)]) {
				x += step;
			}
			/* store the result */
			results[i*SHOTS + j] = (int)x;
		}
	}
	/* print the results */
	for (i = 0; i < CASES*SHOTS; i++) {
		printf((i == CASES*SHOTS - 1) ? "%d\n" : "%d ", results[i]);
	}
	return 0;
}
