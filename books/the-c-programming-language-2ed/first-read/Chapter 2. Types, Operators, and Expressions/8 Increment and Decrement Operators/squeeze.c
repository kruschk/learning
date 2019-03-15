#include <stdio.h>

void squeeze(char s[], int c);

int main(void)
{
	int c = 's';
	char string[] = "This is a string";
	printf("Squeezing \"%s\" with the character '%c'...\n\n", string, c);
	squeeze(string, c);
	printf("Result: \"%s\"", string);
	return 0;
}

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
	int i, j;
	
	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}
