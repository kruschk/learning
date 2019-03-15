#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI acos(-1)

/* describes a point in 2-D space */
struct coords {
	double x;
	double y;
};

struct clock_hand {
	double length; /* length of the hand */
	double angle; /* measured CCW from East */
	struct coords center; /* center point of hand */
	struct coords end_point; /* end point of hand */
};

/* transform_angle: transforms an angle so it goes CCW from 3:00 (normal
 * mathematical convention) instead of CW from 12:00 (a clock's convention) */
double transform_angle(double angle) {
	return -(angle - PI/2.0);
}

/* compute_coordinates: compute the coordinates of the end of a hand centered
 * at a certain point which has a given length is pointing at an angle measured
 * CCW from 3:00 */
void compute_coordinates(struct clock_hand *hand) {
	hand->end_point.x = hand->center.x + hand->length*cos(hand->angle);
	hand->end_point.y = hand->center.y + hand->length*sin(hand->angle);
	return;
}

int main(void) {
	int scan_status;
	unsigned int i, cases;
	/* get the number of cases (each case is a time) */
	scan_status = scanf("%u\n", &cases);
	if (scan_status != 1) {
		fprintf(stderr, "could not read the number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* for each time, compute the coordinates of the ends of the hour and
	 * minute hands */
	for (i = 0; i < cases; i++) {
		unsigned int hours, minutes;
		const struct coords center = {10.0, 10.0};
		struct clock_hand hour_hand, minute_hand;
		/* initialize some of the clock hand members */
		hour_hand.length = 6.0;
		hour_hand.center = center;
		minute_hand.length = 9.0;
		minute_hand.center = center;
		/* get the hours and minutes */
		scan_status = scanf("%u:%u", &hours, &minutes);
		if (scan_status != 2) {
			fprintf(stderr, "error reading set #%u of times\n", i + 1);
			exit(EXIT_FAILURE);
		}
		/* clock time is cyclic in the range [0, 12); take mod 12 so 24-hour
		 * time can be evaluated without any further accomodations */
		hours %= 12;
		/* Convert the hour to radians, measured clockwise from 12:00. The hour
		 * hand moves proportionally to the minute hand, so we add a 1/60th of
		 * of the minutes the hour angle. Then, we convert to radians by
		 * multiplying by 2*PI rad and dividing by 12 hours, which cancels the
		 * units. The hour angle is then transformed so it measures CCW
		 * from 3:00, per mathematical convention. */
		hour_hand.angle = transform_angle(2.0*PI*(hours+minutes/60.0)/12.0);
		/* don't need to account for the hour angle in the minute angle, since
		 * the minute hand doesn't move with the hour hand */
		minute_hand.angle = transform_angle(2.0*PI*minutes/60.0);
		/* compute the coordinates of the end of the hour hand */
		compute_coordinates(&hour_hand);
		/* compute the coordinates of the end of the minute hand */
		compute_coordinates(&minute_hand);
		/* print the results */
		printf("%.8f %.8f %.8f %.8f" , hour_hand.end_point.x, hour_hand.end_point.y,
				minute_hand.end_point.x, minute_hand.end_point.y);
		putchar((i == cases - 1) ? '\n' : ' ');
	}
	return 0;
}
