#include "std_lib_facilities.h"

int main(void) {
	double d = 0;
	while (cin >> d) {
		int i = d;
		char c = i;
		int i2 = c;
		cout << "d: " << d
			<< "\ni: " << i
			<< "\ni2: " << i2
			<< "\nchar(" << c << ")\n";
	}
}
