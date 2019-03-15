/* This solution is from the clc-wiki.net solution by Colin Barker. */
#include <stdio.h>
#include <time.h>

#define MAX_ELEMENT 20000

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

/*  Outputs approximation of processor time required
    for our two binary search functions. We search for
    the element -1, to time the functions' worst case
    performance (i.e. element not found in test data)   */

int main(void) {
    int testdata[MAX_ELEMENT];
    int index;                  /*  Index of found element in test data  */
    int n = 5137;                 /*  Element to search for  */
    int i;
    clock_t time_taken;

    /*  Initialize test data  */
    
    for ( i = 0; i < MAX_ELEMENT; ++i )
        testdata[i] = i;
    
    
    /*  Output approximation of time taken for
        100,000 iterations of binsearch()       */
    
    for ( i = 0, time_taken = clock(); i < 100000; ++i ) {
        index = binsearch(n, testdata, MAX_ELEMENT);
    }
    time_taken = clock() - time_taken;
    
    if ( index < 0 )
        printf("Element %d not found.\n", n);
    else
        printf("Element %d found at index %d.\n", n, index);
    
    printf("binsearch() took %lu clocks (%lu seconds)\n",
           (unsigned long) time_taken,
           (unsigned long) time_taken / CLOCKS_PER_SEC);
    
    
    /*  Output approximation of time taken for
        100,000 iterations of binsearch2()        */
    
    for ( i = 0, time_taken = clock(); i < 100000; ++i ) {
        index = binsearch2(n, testdata, MAX_ELEMENT);
    }
    time_taken = clock() - time_taken;
    
    if ( index < 0 )
        printf("Element %d not found.\n", n);
    else
        printf("Element %d found at index %d.\n", n, index);
    
    printf("binsearch2() took %lu clocks (%lu seconds)\n",
           (unsigned long) time_taken,
           (unsigned long) time_taken / CLOCKS_PER_SEC);
    
    return 0;
}

/*
int main(void) {
	int v[] = {1, 5, 7, 9, 12, 17, 18, 19, 46, 400, 1024, 9001};
	int x = 9001;
	int n = 12;

	int pos = binsearch(x, v, n);
	printf("pos: %d\nvalue: %d\n", pos, v[pos]);

	pos = binsearch2(x, v, n);
	printf("pos: %d\nvalue: %d\n", pos, v[pos]);

	return 0;
}
*/

int binsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid]) {
			high = mid - 1;
		}
		else if (x > v[mid]) {
			low = mid + 1;
		}
		else {
			return mid;
		}
	}

	return -1;
}

int binsearch2(int x, int v[], int n) {
	int low, high, mid;

	low = -1;
	high = n;
	while (low + 1 < high) {
		mid = (low+high)/2;
		if (x > v[mid]) {
			low = mid;
		}
		else {
			high = mid;
		}
	}

	if (high == n || v[high] != x) {
		return -1;
	}
	else {
		return high;
	}
}
