#include "std_lib_facilities.h"

int main(void) {
	string user_name;
	string friend_name;
	string other_name;
	char friend_sex = 0;
	int friend_age = -1;

	cout << "Please type your first name and hit enter: ";
	cin >> user_name;
	cout << "Hello, " << user_name << ".\n";
	cout << "Please enter the name of the person you would like to write to: ";
	cin >> friend_name;
	cout << "Please enter the age of this friend: ";
	cin >> friend_age;
	if (friend_age <= 0 || friend_age >= 110) {
		simple_error("You're kidding!");
	}
	cout << "Please enter the name of another friend: ";
	cin >> other_name;
	cout << "Type the letter 'f' if this friend is female and 'm' if they are male: ";
	cin >> friend_sex;

	cout << "Dear " << friend_name << ",\n\tHow are you? I am fine. We do not see each other much; I would love to visit you sometime. Have you seen " << other_name << " lately? ";
	if (friend_sex == 'f') {
		cout << "If you see " << other_name << " please ask her to call me. ";
	}
	else if (friend_sex == 'm') {
		cout << "If you see " << other_name << " please ask him to call me. ";
	}
	else {
		cout << "If you see " << other_name << " please ask them to call me. ";
	}
	if (friend_age < 12) {
		cout << "Next year you will be " << friend_age + 1 << "!\n";
	}
	else if (friend_age == 17) {
		cout << "Next year you will be able to vote!\n";
	}
	else if (friend_age > 70) {
		cout << "I hope you are enjoying retirement!\n";
	}
	cout << "Yours sincerely,\n\n\n" << user_name << '\n';
}
