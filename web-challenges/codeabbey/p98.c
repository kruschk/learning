#include <math.h>
#include <stdio.h>
#include "custom_round.h"
#define PI acos(-1)

int main(void) {
	/* a point in 2-dimensional space, starting at the origin */
	struct {
		double x;
		double y;
	} treasure = {0.0, 0.0};
	double distance, azimuth;
	while ('\n' != getchar()) { /* ignore first line */
		;
	}
	/* while additional steps are available */
	while (2 == scanf("go %lf feet by azimuth %lf\n", &distance, &azimuth)) {
		/* convert azimuth to mathematical convention (theta = 0 is east) */
		double theta = (90.0 - azimuth)*PI/180.0;
		/* add the map instruction to our coordinates */
		treasure.x += distance*cos(theta);
		treasure.y += distance*sin(theta);
	}
	/* print the results */
	printf("%ld %ld\n", custom_round(treasure.x), custom_round(treasure.y));
	return 0;
}
