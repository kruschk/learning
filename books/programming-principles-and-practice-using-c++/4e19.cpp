// program for chapter 4 exercises 19 through 21

#include "std_lib_facilities.h"

int main (void) {
	vector<string> names;
	vector<int> scores;
	string temp_name;
	int temp_score;

	cout << "Enter a name and a score, separated by a space. \"NoName 0\" to"
			" move on.\n";
	while (cin >> temp_name >> temp_score) {
		if (temp_name == "NoName" && temp_score == 0) {
			break;
		}
		for (string x : names) {
			if (x == temp_name) {
				simple_error("That name has already been entered.\n");
			}
		}

		names.push_back(temp_name);
		scores.push_back(temp_score);
	}

	for (int i = 0; i < names.size(); i++) {
		cout << names[i] << '\t' << scores[i] << '\n';
	}

	cout << "Enter a name to find that person's score. \"exit\" to move on\n";
	while (cin >> temp_name) {
		bool name_found	= false;
		if (temp_name == "exit") {
			break;
		}
		for (int i = 0; i < names.size(); i++) {
			if (names[i] == temp_name) {
				cout << names[i] << '\t' << scores[i] << '\n';
				name_found = true;
			}
		}
		if (!name_found) {
			cout << "name not found\n";
		}
	}

	cout << "Enter an integer to find who has that score. \"-1\" to move on.\n";
	while (cin >> temp_score) {
		bool score_found = false;
		if (temp_score == -1) {
			break;
		}
		for (int i = 0; i < scores.size(); i++) {
			if (scores[i] == temp_score) {
				cout << names[i] << '\t' << scores[i] << '\n';
				score_found = true;
			}
		}
		if (!score_found) {
			cout << "score not found\n";
		}
	}

	return 0;
}
