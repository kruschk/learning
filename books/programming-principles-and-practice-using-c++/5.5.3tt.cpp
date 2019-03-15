// 5.5.3 try this

#include "std_lib_facilities.h"

int area(int length, int width) {
	if (length<=0 || width <=0) {
		throw runtime_error("non-positive area1");
	}
	return length*width;
}

// calculate area within frame
int framed_area(int x, int y) {
	constexpr int frame_width = 2;
	if ((x - frame_width <= 0) || (y - frame_width <= 0)) {
		throw runtime_error("non-positive framed area");
	}
	return area(x - frame_width, y - frame_width);
}

int f(int x, int y, int z) {
	int area1 = area(x, y);
	int area2 = framed_area(3, z);
	int area3 = framed_area(y, z);
	double ratio = double(area1)/area3;

	cout << area1 << '\t' << area2 << '\t' << area3 << '\t' << ratio << '\n';
}

int main(void)
try {
	f(5, 12, 1);
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
