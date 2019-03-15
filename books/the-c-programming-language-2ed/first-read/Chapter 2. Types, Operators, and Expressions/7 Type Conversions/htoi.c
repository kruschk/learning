/* Write the function htoi(s), which converts a string of hexadecimal digits
	(including an optional 0x or 0X) into its equivalent integer value. The
	allowable digits are 0 through 9, a through f, and A through F. */

#include <stdio.h>
#include <math.h>
#define	MAXDIGITS	20

int htoi(char hexstr[]);

int main(void)
{
	char hexnumber[] = "0xF25A9";
	htoi(hexnumber);
	return 0;
}

/* converts a string of hexadecimal digits to a decimal integer. This function
	relies on ASCII encoding. */
int htoi(char hexstr[])
{
	/* checks for a leading 0x or 0X, if found, shifts the array two places to
		the left. */
	if (hexstr[0] == '0' && (hexstr[1] == 'x' || hexstr[1] == 'X'))
	{
		int i = 0;
		while (hexstr[i+2] != '\0')
		{
			hexstr[i] = hexstr[i+2];
			++i;
		}
		hexstr[i] = '\0';
	}
	
	/* makes all the digits lower-case and counts how many digits are in the
		array */
	int count;
	for (count = 0; hexstr[count] != '\0'; count++)
	{
		if (hexstr[count] >= 'A' && hexstr[count] <= 'Z')
		{
			hexstr[count] = hexstr[count] + 'a' - 'A';
		}
	}
	--count;	/* so that count is 0-based */
	
	/* reverses the array so that the least significant digit will match with
		the 0 index of the array and the most significant digit will match with
		the greatest occupied index of the array. */
	int i = 0;
	char hexreverse[MAXDIGITS];
	while (i <= count)
	{
		hexreverse[i] = hexstr[count-i];
		++i;
	}
	hexreverse[i] = '\0';
	
	/* converts the different digits in the array to their decimal equivalents,
		i.e. f = 15, e = 14, etc. */
	i = 0;
	while (hexreverse[i] != '\0')
	{
		if (hexreverse[i] >= '0' && hexreverse[i] <= '9')
		{
			hexreverse[i] -= '0';
		}
		else if (hexreverse[i] >= 'a' && hexreverse[i] <= 'f')
		{
			hexreverse[i] -= 87;
		}
		
		++i;
	}
	
	/* finally, this portion of the function converts the string of digits to
		a decimal integer. */
	int result = 0;
	for (i = 0; hexreverse[i] != '\0'; ++i)
	{
		result += hexreverse[i] * (int)pow(16, i);
	}
	
	printf("The hexadecimal number %s, in decimal form, is: %d", hexstr, result);
	
	return result;
}