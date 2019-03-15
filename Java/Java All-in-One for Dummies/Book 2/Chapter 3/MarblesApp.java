/* Listing 3-1: A program that divvies up marbles.
   Given x marbles and y children, this app tells you how many marbles to give
   to each child, and how many will be left over. */

import java.util.Scanner;

public class MarblesApp
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		// Declare local variables.
		int numberOfMarbles;
		int numberOfChildren;
		int marblesPerChild;
		int marblesLeftOver;
		
		// Get the input data from the user.
		System.out.println("Welcome to the marble divvy-upper.");
		System.out.print("Number of marbles: ");
		numberOfMarbles = sc.nextInt();
		System.out.print("Number of children: ");
		numberOfChildren = sc.nextInt();
		
		// Calculate the results.
		
		marblesPerChild = numberOfMarbles / numberOfChildren;
		marblesLeftOver = numberOfMarbles % numberOfChildren;
		
		// Print the results.
		System.out.println("Give each child " + marblesPerChild + " marbles.");
		System.out.println("You will have " + marblesLeftOver + " marbles left over.");
	}
}