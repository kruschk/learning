// converts miles to kilometers, based on user input

#include "std_lib_facilities.h"

int main(void) {
	double miles = -1.0;
	cout << "Please enter the number of miles to conver to kilometers: ";
	cin >> miles;
	cout << "That equates to " << miles * 1.609 << " kilometers.\n";
}
