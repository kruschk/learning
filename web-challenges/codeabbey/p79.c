#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES ('Z' - 'A' + 1)
#define STACK_SIZE 4096

enum boolean {FALSE, TRUE};
enum status {ACYCLIC, CYCLIC};

/* stack structure */
struct stack {
	unsigned short int length;
	char element[STACK_SIZE];
};

/* a city has a name and an array of pointers to other cities (the roads) */
struct city {
	char name; /* city name, which is just one character */
	unsigned short int length;
	struct city *roads[MAX_CITIES]; /* array of pointers to other cities */
};

/* list of all the cities */
struct city_list {
	unsigned short int length;
	struct city cities[MAX_CITIES];
};

/* find_city: return the index of the city with the name member equal to name,
 * or -1 if it's not present */
struct city *find_city(struct city_list *city_list, char name) {
	unsigned short int i;
	for (i = 0; i < city_list->length; i++) {
		if (city_list->cities[i].name == name) {
			return &city_list->cities[i];
		}
	}
	return NULL;
}

/* add_city: add city with name name to the city list, and return its index in
 * the list */
struct city *add_city(struct city_list *city_list, char name) {
	struct city *city_p;
	city_p = &city_list->cities[city_list->length];
	city_list->length++;
	city_p->name = name;
	city_p->length = 0;
	return city_p;
}

/* add_road: add a road between two cities */
void add_road(struct city *left_city, struct city *right_city) {
	if (left_city->length >= MAX_CITIES || right_city->length >= MAX_CITIES) {
		fprintf(stderr, "add_road: too many roads between cities %c and %c\n",
				left_city->name, right_city->name);
	}
	left_city->roads[left_city->length] = right_city;
	left_city->length++;
	right_city->roads[right_city->length] = left_city;
	right_city->length++;
	return;
}

/* print_city_list: print the properties of each city in the list */
void print_city_list(struct city_list city_list) {
	unsigned short int i;
	for (i = 0; i < city_list.length; i++) {
		unsigned short int k;
		printf("%c: ", city_list.cities[i].name);
		printf("%hu ", city_list.cities[i].length);
		printf("me: %p, ", (void *)&city_list.cities[i]);
		for (k = 0; k < city_list.cities[i].length; k++) {
			printf("%p ", (void *)city_list.cities[i].roads[k]);
		}
	}
	putchar('\n');
}

/* stack_has_name: check if the name stack contains the given name */
enum boolean stack_has_name(struct stack *name_stack, char name) {
	unsigned short int i;
	for (i = 0; i < name_stack->length; i++) {
		if (name_stack->element[i] == name) {
			return TRUE;
		}
	}
	return FALSE;
}

/* push: push a name onto the name stack */
void push(struct stack *name_stack, char name) {
	name_stack->element[name_stack->length] = name;
	name_stack->length++;
	return;
}

/* pop: pop a name off of the name stack */
char pop(struct stack *name_stack) {
	name_stack->length--;
	return name_stack->element[name_stack->length];
}

/* graph_has_duplicate_roads: check if the graph has any duplicate roads. This
 * indicates a cyclic graph, but won't be caught by check_graph_for_cycles. */
enum boolean graph_has_duplicate_roads(struct city_list *city_list) {
	unsigned short int i;
	for (i = 0; i < city_list->length; i++) {
		unsigned short int j;
		struct city city = city_list->cities[i];
		/* nested loop checks for duplicate roads, i.e. two identical pointers
		 * in city.roads[] */
		for (j = 0; j < city.length; j++) {
			unsigned short int k;
			for (k = j + 1; k < city.length; k++) {
				if (city.roads[j] == city.roads[k]) {
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

/* check_graph_for_cycles: recursively check the graph for cycles, and return
 * CYCLIC if it is, ACYCLIC if not */
enum status check_graph_for_cycles(struct stack *name_stack,
		struct city *current_city, struct city *last_city) {
	/* if we've encountered this name before, the graph must be cyclic */
	if (stack_has_name(name_stack, current_city->name)) {
		return CYCLIC;
	}
	else {
		unsigned short int i;
		/* push this name onto the name_stack */
		push(name_stack, current_city->name);
		for (i = 0; i < current_city->length; i++) {
			struct city *next_city = current_city->roads[i];
			/* do not go backward down the same path we just came from; this
			 * prevents going to one node, then coming straight back and
			 * thinking the graph is cyclic (even though I think it technically
			 * is cyclic if this is possible) */
			if (next_city == last_city) {
				continue;
			}
			/* Recursively descend down the nodes and check for a cycle. If we
			 * find a cycle, we can return immediately. */
			else if (check_graph_for_cycles(name_stack, next_city,
						current_city) == CYCLIC) {
				return CYCLIC;
			}
		}
		/* pop the last name (which will be this name) off the stack */
		pop(name_stack);
	}
	/* if we've made it this far, the graph is acyclic */
	return ACYCLIC;
}

int main(void) {
	unsigned short int cases, i;
	/* get the number of test cases */
	if (1 != scanf("%hu\n", &cases)) {
		fprintf(stderr, "error reading number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* determine if there are any cycles for each test case */
	for (i = 0; i < cases; i++) {
		struct city_list city_list;
		struct stack name_stack;
		unsigned short int roads, j;
		enum status status;
		/* make sure city_list starts with a length of 0 */
		city_list.length = 0;
		name_stack.length = 0;
		/* get the number of roads */
		if (1 != scanf("%hu\n", &roads)) {
			fprintf(stderr, "error reading number of roads on line %hu\n",
					i+2);
			exit(EXIT_FAILURE);
		}
		/* generate the graph */
		for (j = 0; j < roads; j++) {
			struct city *left_city_p, *right_city_p;
			char left_city_name, right_city_name;
			/* get the city name to the left of the dash and to the right from
			 * input */
			if (2 != scanf(" %c-%c ", &left_city_name, &right_city_name)) {
				fprintf(stderr, "error reading road %hu on line %hu\n", j+1,
						i+2);
				exit(EXIT_FAILURE);
			}
			/* if either city is not yet on the city list, add it to the list */
			if ((left_city_p = find_city(&city_list, left_city_name)) == NULL) {
				left_city_p = add_city(&city_list, left_city_name);
			}
			if ((right_city_p = find_city(&city_list, right_city_name)) == NULL) {
				right_city_p = add_city(&city_list, right_city_name);
			}
			/* connect the two cities with a road */
			add_road(left_city_p, right_city_p);
		}
		/* print the graph */
		/*print_city_list(city_list);*/
		/* check the graph for cycles */
		if (graph_has_duplicate_roads(&city_list)) {
			status = CYCLIC;
		}
		else {
			status = check_graph_for_cycles(&name_stack, &city_list.cities[0], &city_list.cities[0]);
		}
		/* print the results */
		printf((i == cases - 1) ? "%hu\n" : "%hu ", status);
	}
	return 0;
}
