#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "rand_gen.h"
#include "heap.h"
#define SCALE 999

/* a struct describing a hungry person */
struct hungry_person {
	unsigned int starvation_degree;
	unsigned int arrival_time;
	unsigned int personal_discomfort;
};

/* a struct which contains an array of hungry people */
struct hungry_people {
	unsigned int index;
	unsigned int number;
	struct hungry_person *person;
};

/* comparison function for comparing one hungry person to another */
int hungry_person_compare(const void *keyval, const void *datum) {
	/* if the two people have the same degree of starvation, prioritize the one
	 * who arrived earlier */
	if ((*(struct hungry_person *)keyval).starvation_degree
		== (*(struct hungry_person *)datum).starvation_degree) {
		return (*(struct hungry_person *)datum).arrival_time
			- (*(struct hungry_person *)keyval).arrival_time;
	}
	else {
		return (*(struct hungry_person *)keyval).starvation_degree
			- (*(struct hungry_person *)datum).starvation_degree;
	}
}

int main(void) {
	/* period of arrival of hungry people */
	const unsigned int arrival_period = 1;
	/* period of production of food */
	const unsigned int production_period = 2;
	unsigned int people, seed, clock;
	struct hungry_people hungry_people;
	Heap h;
	enum heap_error heap_extract_status;
	unsigned long int total_discomfort;
	/* get the number of people and the random number seed value from input */
	if (2 != scanf("%u %u\n", &people, &seed)) {
		fprintf(stderr, "error reading the number of people or seed value\n");
		exit(EXIT_FAILURE);
	}
	/* initialize the heap */
	heap_init(NULL, &h, HEAP_MAX, people);
	/* initialize the hungry people array */
	hungry_people.index = 0;
	hungry_people.number = people;
	hungry_people.person
		= malloc(hungry_people.number*sizeof *hungry_people.person);
	/* add the first (0th) arrival to the heap */
	seed = lcg(seed, 445, 700001, 2097152);
	hungry_people.person[hungry_people.index].starvation_degree
		= normalize(seed, SCALE, 1);
	hungry_people.person[hungry_people.index].arrival_time = 0;
	heap_insert(NULL, &h, &hungry_people.person[hungry_people.index],
			hungry_person_compare);
	/* print details */
	printf("t = 0\t");
	printf("visitor with degree %u came\n",
			hungry_people.person[hungry_people.index].starvation_degree);
	/* prepare ourselves for the next arrival */
	(hungry_people.index)++;
	for (clock = 1, total_discomfort = 0; clock <= people*production_period; clock++) {
		/* print details */
		printf("t = %u\t", clock);
		/* update the personal discomfort of all the hungry people (this would
		 * be useful if we were prioritizing based on personal discomfort;
		 * alas, we are only prioritizing by starvation degree */
		/*for (i = 0; i < h.next_index; i++) {
			struct hungry_person *hp = h.array[i];
			hp->personal_discomfort += hp->starvation_degree;
		}*/
		/* only need to re-heapify if we're prioritizing based on personal
		 * discomfort; however, the starvation degree is constant so we don't
		 * have to */
		/*heap_heapify(NULL, &h, hungry_person_compare);*/
		/* some food has been produced can give it to a hungry person */
		if (0 == clock%production_period) {
			/* the next person is on the top of the heap */
			struct hungry_person *hp =
				heap_extract(&heap_extract_status, &h, hungry_person_compare);
			/* break out of the loop if the extract was not successful */
			if (HEAP_SUCCESS != heap_extract_status) {
				break;
			}
			/* add his discomfort to the total discomfort */
			hp->personal_discomfort =
				hp->starvation_degree*(clock - hp->arrival_time);
			total_discomfort += hp->personal_discomfort;
			/* print details */
			printf("visitor with degree %u left, arrived at %u, (+%u)\n",
					hp->starvation_degree, hp->arrival_time, hp->personal_discomfort);
		}
		/* A new hungry person arrives. Note: we subtract 1 from
		 * people*arrival_period because we initialize clock = 0 outside the
		 * loop. */
		if (0 == clock%arrival_period && clock < people*arrival_period) {
			struct hungry_person *hp = &hungry_people.person[hungry_people.index];
			/* assign the new seed value */
			seed = lcg(seed, 445, 700001, 2097152);
			/* this person has a starvation degree related to the random value */
			hp->starvation_degree = normalize(seed, SCALE, 1);
			/* personal discomfort is initialized to 0, and will be updated later */
			hp->personal_discomfort = 0;
			hp->arrival_time = clock;
			/* add this person to the heap (priority queue) */
			heap_insert(NULL, &h, hp, hungry_person_compare);
			/* print details */
			printf("visitor with degree %u came\n", hp->starvation_degree);
			/* prepare ourselves for the next hungry_person from the array */
			(hungry_people.index)++;
		}
	}
	/* print the result */
	printf("%lu\n", total_discomfort);
	/* clean up */
	free(hungry_people.person);
	heap_clear(&h);
	return 0;
}
