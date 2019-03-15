// Similar to Dodecaphobia, except it lets the user decide when to quit.

import java.util.Scanner;

public class NumberPhobia
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		int number = 0;
		String input;
		while (true)
		{
			System.out.println(number + " ");
			System.out.print("Do you want to keep counting?" + " (Y or N) ");
			input = sc.next();
			if (input.equalsIgnoreCase("N"))
				break;
			number += 1;
		}
		System.out.println("\nWhew! That was close.\n");
	}
}