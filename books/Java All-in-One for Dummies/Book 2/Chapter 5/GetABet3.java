/* GetABet with slightly less repetitive and slightly more understandable input
   validation. */

import java.util.Scanner;

public class GetABet3
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		int bank = 1000;		// Assume the user has 1,000.00.
		int bet;				// The bet entered by the user.
		boolean validBet;		// Indicates whether or not the bet is valid.
		System.out.println("You can bet between 1 and " + bank);
		
		do
		{
			System.out.print("Enter your bet: ");
			bet = sc.nextInt();
			validBet = true;
			if ((bet <= 0) || (bet > bank))
				validBet = false;
				System.out.println("What, are you crazy?");
		} while (!validBet);
		System.out.println("Your money's good here.");
	}
}