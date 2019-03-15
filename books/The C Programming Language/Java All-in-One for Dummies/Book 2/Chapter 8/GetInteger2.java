/* Listing 8-2: Another version of the GetInteger method.
   The book says method, shouldn't it say class?? */

import java.util.*;

public class GetInteger2
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		System.out.print("Enter an integer: ");
		int i = getAnInteger();
		System.out.println("You entered " + i + ".");
	}
	
	public static int getAnInteger()
	{
		while (!sc.hasNextInt())
		{
			sc.nextLine();
			System.out.print("That's not an integer. Try again: ");
		}
		return sc.nextInt();
	}
}