/* Exercise 2-4. Write an alternate version of squeeze(s1,s2) that deletes each
	character in s1 that matches any character in the string s2. */

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void)
{
	char s1[] = "googoo";
	char s2[] = "porridge";		/* result of "stringy" and "pray" should be "sting" */
	printf("Squeezing the strings \"%s\" and \"%s\"...\n", s1, s2);
	squeeze(s1, s2);
	printf("The result is: \"%s\"", s1);
	return 0;
}

void squeeze(char s1[], char s2[])
{
	int i, j, k;

	k = 0;

	while (s2[k++] != '\0')		/* loop through the second string, post-incrementing k on each loop */
	{
		for (i = j = 0; s1[i] != '\0'; i++)		/* loop until the end of the first string is reached */
		{
			if (s1[i] != s2[k])		/* if i-th character in the first string is not equal to the k-th character in the second string: */
			{
				s1[j++] = s1[i];	/* set the j-th character in the first string to the i-th character in the first string, then increment j */
			}
		}

		s1[j] = '\0';	/* terminate the first string so that we never accidentally end up with extra characters. */
	}
}