// 5_d.cpp: chapter 5 drill

#include "std_lib_facilities.h"

int main()
try {
	// 1.
		cout << "1Success!\n";
	// 2.
		cout << "2Success!\n";
	// 3.
		cout << "3Success" << "!\n";
	// 4.
		string success = "4Success!";
		cout << success << '\n';
	// 5.
		int res = 7;
		vector<int> v5(10);
		v5[5] = res;
		cout << "5Success!\n";
	// 6.
		vector<int> v6(10);
		v6[5] = 7;
		if (v6[5]==7) {
			cout << "6Success!\n";
		}
	// 7.
		if (bool cond7 = true) {
			cout << "7Success!\n";
		}
		else {
			cout << "7Fail!\n";
		}

	// 8.
		bool c8 = true;
		if (c8) {
			cout << "8Success!\n";
		}
		else {
			cout << "8Fail!\n";
		}
	// 9.
		string s9 = "ape";
		bool c9 = "fool" > s9;
		if (c9) {
			cout << "9Success!\n";
		}
	// 10.
		string s10 = "ape";
		if (s10!="fool") {
			cout << "10Success!\n";
		}
	// 11.
		string s11 = "ape";
		if (s11=="fool") {
			cout << "11Success!\n";
		}
	// 12.
		string s12 = "ape";
			if (s12+"fool"=="apefool") {
				cout << "12Success!\n";
		}
	// 13.
		vector<char> v13(5);
		for (int i=0; i<v13.size(); ++i) {
			cout << "13Success!\n";
		}
	// 14.
		vector<char> v14(5);
		for (int i=0; i<v14.size(); ++i) {
			cout << "14Success!\n";
		}
	// 15.
		string s15 = "15Success!\n";
		for (int i=0; i<s15.size(); ++i) {
			cout << s15[i];
		}
	// 16.
		if (true) {
			cout << "16Success!\n";
		}
			else {
				cout << "16Fail!\n";
		}
	// 17.
		int x17 = 2000;
		char c17 = x17;
		if (c17==-48) {
			cout << "17Success!\n";
		}
	// 18.
		string s = "18Success!\n";
		for (int i=0; i<s.size(); ++i) {
			cout << s[i];
		}
	// 19.
		vector<int> v19(5);
		for (int i=0; i<v19.size(); ++i) {
			cout << "19Success!\n";
		}
	// 20.
		int i20 = 0;
		int j20 = 0;
		while (i20<10) {
			++i20;
		}
		if (j20<i20) {
			cout << "20Success!\n";
		}
	// 21.
		int x21 = 3;
		double d21 = 5.0/(x21-2.0);
		if (d21==5.0) {
			cout << "21Success!\n";
		}
	// 22.
		string s22 = "22Success!\n";
		for (int i22=0; i22<=10; ++i22) {
			cout << s22[i22];
		}
	// 23.
		int i23=0;
		int j23=0;
		while (i23<10) {
			++i23;
		}
		if (j23<i23) {
			cout << "23Success!\n";
		}
	// 24.
		int x24 = 4;
		double d24 = 5/(x24-2);
		if (d24=2*x24+0.5) {
			cout << "24Success!\n";
		}
	// 25. 
		cout << "25Success!\n";

	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	return 2;
}
