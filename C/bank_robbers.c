#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool array_is_zero(unsigned *arr, unsigned len) {
    for (unsigned i = 0; i < len; i++) {
        if (arr[i]) {
            return false;
        }
    }
    return true;
}

unsigned min(unsigned *arr, unsigned len, unsigned *index) {
    unsigned min_elem = arr[0];
    unsigned min_index = 0;
    for (unsigned i = 1; i < len; i++) {
        if (arr[i] < min_elem) {
            min_elem = arr[i];
            min_index = i;
        }
    }
    if (index) {
        *index = min_index;   
    }
    return min_elem;
}

void subtract_from_each(unsigned *arr, unsigned len, unsigned value) {
    for (unsigned i = 0; i < len; i++) {
        arr[i] -= value;   
    }
    return;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main() {
    unsigned R, V;
    scanf("%u%u", &R, &V);
    unsigned *time_to_crack = malloc(V*sizeof *time_to_crack);
    for (unsigned i = 0; i < V; i++) {
        int C, N;
        scanf("%d%d", &C, &N);
        time_to_crack[i] = pow(10, N)*pow(5, (C - N));
        fprintf(stderr, "%d, %d, %d ", C, N, time_to_crack[i]);
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    //printf("1\n");
    if (R > V) {R = V;}
    int *robbers = malloc(R*sizeof *robbers);
    for (unsigned i = 0; i < R; i++) {
        robbers[i] = i;   
    }
    unsigned lowest_robber = 0;
    unsigned highest_robber = R;
    unsigned total_time = 0;
    while (!array_is_zero(time_to_crack, V)) {
        unsigned min_time = min(arr, 
    }

    return 0;
}