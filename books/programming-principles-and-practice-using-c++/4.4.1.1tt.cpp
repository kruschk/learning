// convert from inches to centimeters or centimeters to inches
// a suffix ‘i’ or ‘c’ indicates the unit of the input
// any other suffix is an error

#include "std_lib_facilities.h"

int main() {
	constexpr double euro_to_dollar = 1.13;		// 1 euro = 1.13 USD
	constexpr double pound_to_dollar = 1.29;	// 1 pound = 1.29 USD
	constexpr double yen_to_dollar = 0.0091;	// 1 yen = 0.0091 USD

	double amount = 1;	// amount of money in euro, pound, or yen
	char unit = ' ';	// a space is not a unit

	cout << "Please enter an amount of money followed by a unit (e, p, or y): ";
	cin >> amount >> unit;

	if (unit == 'e') {
		cout << amount << " euro = " << amount*euro_to_dollar << " USD\n";
	}
	else if (unit == 'p') {
		cout << amount << " pounds = " << amount*pound_to_dollar << " USD\n";
	}
	else if (unit == 'y') {
		cout << amount << " yen = " << amount*yen_to_dollar << " USD\n";
	}
	else {
		cout << "Sorry, I don't know a unit called '" << unit << "'\n";
	}
}
