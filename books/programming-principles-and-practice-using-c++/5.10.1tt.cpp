#include "std_lib_facilities.h"

// calculate area of a rectangle;
// pre-conditions: length and width are positive
// post-condition: returns a positive value that is the area
int area(int length, int width) {
	if (length<=0 || width <=0) error("area() pre-condition");
	int a = length*width;
	if (a<=0) error("area() post-condition");
	return a;
}

int main(void) {
	cout << area(2000000, 3) << '\n';
}
