/* Exercise 2-5. Write the function any(s1,s2), which returns the first
	location in the string s1 where any character from the string s2 occurs, or
	-1 if s1 contains no characters from s2. (The standard library function
	strpbrk does the same job but returns a pointer to the location.) */

#include <stdio.h>

int any(char s1[], char s2[]);

int main(void)
{
	char s1[] = "This is a string.";
	char s2[] = "Pleasure to meet you, string!";
	
	printf("%d", any(s1, s2));
}

int any(char s1[], char s2[])	/* function returns the index of the string, counting from 0 it should be correct */
{
	int i, j;
	
	j = 0;
	while (s2[j++] != '\0')
	{
		for (i = 0; s1[i] != '\0'; i++)
		{
			if (s1[i] == s2[j])
			{
				return i;
			}
		}
	}
	
	return -1;
}