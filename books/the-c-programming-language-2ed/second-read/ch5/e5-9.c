#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int day_of_year2(int year, int month, int day);
void month_day2(int year, int yearday, int *pmonth, int *pday);

int main(void) {
	int year = 1995;
	int month = 4;
	int day = 9;
	int year_day;

	/*
	printf("yyyy-mm-dd: %4d-%02d-%02d\n", year, month, day);

	year_day = day_of_year(year, month, day);
	printf("Day of year: %d\n", year_day);

	month_day(year, year_day, &month, &day);
	printf("mm-dd: %02d-%02d\n", month, day);
	*/
	
	printf("yyyy-mm-dd: %4d-%02d-%02d\n", year, month, day);

	year_day = day_of_year2(year, month, day);
	printf("Day of year: %d\n", year_day);

	month_day2(year, year_day, &month, &day);
	printf("mm-dd: %02d-%02d\n", month, day);

	return 0;
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}

/* day_of_year2: set day of year from month & day, pointer version */
int day_of_year2(int year, int month, int day) {
	int leap;
	char *temp_ptr;

	leap = ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
	temp_ptr = &daytab[leap][1];
	while (temp_ptr - &daytab[leap][0] < month) {
		day += *temp_ptr;
		temp_ptr++;
	}
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}

/* month_day2: set month, day from day of year, pointer version */
void month_day2(int year, int yearday, int *pmonth, int *pday) {
	int leap;
	char *position_ptr;

	leap = ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
	position_ptr = &daytab[leap][1];
	while (yearday > *position_ptr) {
		yearday -= *position_ptr;
		position_ptr++;
	}
	*pmonth = position_ptr - &daytab[leap][0];
	*pday = yearday;
}
