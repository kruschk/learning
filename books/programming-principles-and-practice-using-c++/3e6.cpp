#include "std_lib_facilities.h"

int main(void) {
	int i1;
	int i2;
	int i3;

	cout << "Please type three integers separated by spaces, then hit enter: ";
	cin >> i1;
	cin >> i2;
	cin >> i3;

	int smallest = i1;
	int middle = i2;
	int largest = i3;

	if ((i1 < i3) && (i1 < i2)) {
		smallest = i1;
		if (i3 < i2) {
			middle = i3;
			largest = i2;
		}
		else if (i2 < i3) {
			middle = i2;
			largest = i3;
		}
	}
	else if ((i2 < i1) && (i2 < i3)) {
		smallest = i2;
		if (i3 < i1) {
			middle = i3;
			largest = i1;
		}
		else if (i1 < i3) {
			middle = i1;
			largest = i3;
		}
	}
	else if ((i3 < i2) && (i3 < i1)) {
		smallest = i3;
		if (i2 < i1) {
			middle = i2;
			largest = i1;
		}
		else if (i1 < i2) {
			middle = i1;
			largest = i2;
		}
	}

	cout << "smallest: " << smallest
		<< "\nmiddle: " << middle
		<< "\nlargest: " << largest
		<< '\n';
}
