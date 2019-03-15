// Similar to NumberPhobia, except it tests the input differently.

import java.util.Scanner;

public class NumberPhobia2
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		int number = 2;
		String input = "Y";
		while (input.equalsIgnoreCase("Y"))
		{
			System.out.println(number + " ");
			System.out.print("Do you want to keep counting?" + " (Y or N) ");
			input = sc.next();
			if (input.equalsIgnoreCase("N"))
				break;
			number += 2;
		}
		System.out.println("\nWhew! That was close.\n");
	}
}