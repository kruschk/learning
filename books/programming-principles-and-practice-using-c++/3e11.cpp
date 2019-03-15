// chapter 3 exercise 11: converts coins to dollars and cents

#include "std_lib_facilities.h"

int main(void) {
	// initialize variables
	int pennies = 0;
	int nickels = 0;
	int dimes = 0;
	int quarters = 0;
	int half_dollars = 0;
	int dollars = 0;
	double total = 0.0;

	// gather user input
	cout << "How many pennies? ";
	cin >> pennies;
	cout << "How many nickels? ";
	cin >> nickels;
	cout << "How many dimes? ";
	cin >> dimes;
	cout << "How many quarters? ";
	cin >> quarters;
	cout << "How many half-dollars? ";
	cin >> half_dollars;
	cout << "How many dollar coins? ";
	cin >> dollars;

	// output number of each coin, and handle grammar (plural vs. singular)
	if (pennies == 1.0) {
		cout << "You have 1 penny.\n";
	}
	else {
		cout << "You have " << pennies << " pennies.\n";
	}
	if (nickels == 1.0) {
		cout << "You have 1 nickel.\n";
	}
	else {
		cout << "You have " << nickels << " nickels.\n";
	}
	if (dimes == 1.0) {
		cout << "You have 1 dime.\n";
	}
	else {
		cout << "You have " << dimes << " dimes.\n";
	}
	if (quarters == 1.0) {
		cout << "You have 1 quarter.\n";
	}
	else {
		cout << "You have " << quarters << " quarters.\n";
	}
	if (half_dollars == 1.0) {
		cout << "You have 1 half-dollar.\n";
	}
	else {
		cout << "You have " << half_dollars << " half-dollars.\n";
	}
	if (dollars == 1.0) {
		cout << "You have 1 dollar.\n";
	}
	else {
		cout << "You have " << dollars << " dollars.\n";
	}

	// compute the total and output the result
	total = 0.01*(double)pennies + 0.05*(double)nickels + 0.10*(double)dimes +
			0.25*(double)quarters + 0.50*(double)half_dollars + (double)dollars;
	cout << "The value of all your coins is $" << total << '\n';
}
