/* A more obscure usage of for loops that could come in handy sometimes.
   This script takes advantage of the fact that the initialization and count
   expressions can actually be a list of expressions separated by commas. Very
   useful for keeping track of two separate counter variables! */

public class CountBothWays
{
	public static void main(String[] args)
	{
		int a, b;	/* Necessary! Can't declare multiple variables in a for
		loop, i.e. for (int a, int b; ...; ...) won't work! */
		for (a = 1, b = 10; a <= 100 && b >= 0; a++, b--) /* The
		a <= 100 && b >= -2 part is redundant, only one or the other is
		necessary, (i.e. a <= 10;)but note that boolean operators can be used
		in the test expression. */
			System.out.println(a + " " + b);
	}
}