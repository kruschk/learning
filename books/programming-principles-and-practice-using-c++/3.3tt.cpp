// gets the user's name and age, says "hello", and prints the age in months

#include "std_lib_facilities.h"

int main(void) {
	cout << "Please enter your first name and age\n";
	string first_name;
	double age;
	cin >> first_name;
	cin >> age;
	age *= 12;
	cout << "Hello, " << first_name << " (age in months: " << age << ")\n";
	return 0;
}
