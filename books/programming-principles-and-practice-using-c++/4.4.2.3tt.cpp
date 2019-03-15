#include "std_lib_facilities.h"

int main(void) {
	/*
	char letter = 'a';
	while (letter <= 'z') {
		cout << letter << '\t' << int{letter} << '\n';
		letter++;
	}
	*/

	for (char i = '0'; i <= '9'; i++) {
		cout << i << '\t' << int{i} << '\n';
	}

	for (char i = 'A'; i <= 'Z'; i++) {
		cout << i << '\t' << int{i} << '\n';
	}

	for (char i = 'a'; i <= 'z'; i++) {
		cout << i << '\t' << int{i} << '\n';
	}
}
