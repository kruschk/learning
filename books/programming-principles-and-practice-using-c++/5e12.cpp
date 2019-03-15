// chapter 5 exercise 12: bulls and cows game

#include "std_lib_facilities.h"
#define DIGITS 4

const string prompt = "Enter 4 digits between 0 and 9 inclusive, separated by whitespace: ";
int answer[DIGITS] = {-1};
int numbers[DIGITS] = {-1};
int bull_count = 0;
int cow_count = 0;
bool bulls[DIGITS] = {false};
bool match_somewhere[DIGITS] = {false};

void get_nums(void);
void reset_sieves(void);
void sieve(void);
void count_hits(void);

int main(void)
try {
	//answer[DIGITS] = {4, 9, 1, 2};//{randint(10), randint(10), randint(10), randint(10)};
	unsigned int seed;
	cout << "Enter an integer: ";
	cin >> seed;
	srand(seed);
	for (int i = 0; i < DIGITS; i++) {
		answer[i] = randint(1);
	}

	for (int i = 0; i < DIGITS; i++) {
		cout << answer[i] << ' ';
	}
	cout << '\n';

	cout << prompt;
	while (true) {
		bull_count = 0;
		cow_count = 0;
		reset_sieves();

		get_nums();
		sieve();
		count_hits();
		
		cout << bull_count << " bull(s) and " << cow_count << " cow(s)\n";
		if (bull_count == DIGITS) {
			cout << "You win!\n";
			return 0;
		}
	}
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Oops: unkown exception!\n";
	return 2;
}

void get_nums (void) {
	for (int i = 0; i < DIGITS; i++) {
		cin >> numbers[i];
		if (numbers[i] < 0 || numbers[i] > 9) {
			error(prompt);
		}
	}
}

void reset_sieves(void) {
	for (int i = 0; i < DIGITS; i++) {
		bulls[i] = false;
		match_somewhere[i] = false;
	}
}

void sieve(void) {
	for (int i = 0; i < DIGITS; i++) {
		for (int j = 0; j < DIGITS; j++) {
			if (numbers[i] == answer[j]) {
				match_somewhere[i] = true;
			}
		}
		if (numbers[i] == answer[i]) {
			bulls[i] = true;
		}
	}
}

void count_hits(void) {
	for (int i = 0; i < DIGITS; i++) {
		if (bulls[i]) {
			bull_count++;
		}
		if (!bulls[i] && match_somewhere[i]) {
			cow_count++;
		}
	}
}
