#include <stdio.h>
#include <C:\Users\Jonah Kruschke\Documents\Programming\C\The C Programming Language\Chapter 3. Control Flow\3.6 Loops - Do-While\3-4.c>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
	int i = 0x80000000;	//-2147483648;
	char str1[25];
	itoa(i, str1);
	printf("%s\n", str1);
	
	int j = -2147483647;
	char str2[25];
	itoa(j, str2);
	printf("%s\n", str2);
	
	int k = -46;
	char str3[25];
	itoa(k, str3);
	printf("%s\n", str3);
	
	int l = 0;
	char str4[25];
	itoa(l, str4);
	printf("%s\n", str4);
	
	int m = 2147483647;
	char str5[25];
	itoa(m, str5);
	printf("%s\n", str5);
}