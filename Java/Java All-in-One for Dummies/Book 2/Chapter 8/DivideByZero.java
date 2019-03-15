// A simple example of exception handling, illustrated by dividing by zero.

public class DivideByZero
{
	public static void main(String[] args)
	{
		int a = 5;
		int b = 0;			// You know this won't work.
		try
		{
			int c = a / b;	// But you try it anyway.
		}
		catch (ArithmeticException e)		// I think e is an identifier that represents an object of type (class?) ArithmeticException. Sort of like a variable.
		{
			System.out.println("Oops, you can't divide by zero.");
			System.out.print(e);
		}
	}
	
}