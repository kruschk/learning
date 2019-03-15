// Example of how do-while loops are useful for validating input from the user.

import java.util.Scanner;

public class GetABet
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		int bank = 1000;		// Assume the user has $1,000.00.
		int bet;				// The bet entered by the user.
		
		System.out.println("You can bet between 1 and " + bank);
		
		do
		{
			System.out.print("Enter your bet: ");
			bet = sc.nextInt();
		} while ((bet <= 0) || (bet > bank));
		System.out.println("Your money's good here.");
	}
}