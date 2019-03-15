#include "std_lib_facilities.h"

double unit_conversion(double, string);

int main(void) {
	vector<double> record;
	double number, smallest, largest;
	string unit = "|";
	double sum = 0;

	cin >> number >> unit;
	number = unit_conversion(number, unit);
	smallest = largest = number;
	cout << number << " m, the smallest and the largest so far!\n";
	sum += number;
	record.push_back(number);

	while (cin >> number >> unit) {
		number = unit_conversion(number, unit);
		if (number < smallest) {
			smallest = number;
			cout << smallest << " m, the smallest so far\n";
		}
		else if (number > largest) {
			largest = number;
			cout << largest << " m, the largest so far\n";
		}
		else {
			cout << number << " m\n";
		}
		record.push_back(number);
		sum += number;
	}

	cout << "smallest:\n\t" << smallest << " m\n";
	cout << "largest:\n\t" << largest << " m\n";
	cout << "number of values:\n\t" << record.size() << '\n';
	cout << "sum of values entered:\n\t" << sum << " m\n";

	sort(record.begin(), record.end());
	cout << "Entered values (in ascending order):\n";
	for (double x : record) {
		cout << '\t' << x << " m\n";
	}
}

// converts to m
double unit_conversion(double d, string s) {
	if (s == "cm") {
		return d/100.0;
	}
	else if (s == "in") {
		return d*2.54/100.0;
	}
	else if (s == "ft") {
		return d*12.0*2.54/100.0;
	}
	else if (s == "m") {
		return d;
	}
	else {
		simple_error("Illegal unit.\n");
	}
}
