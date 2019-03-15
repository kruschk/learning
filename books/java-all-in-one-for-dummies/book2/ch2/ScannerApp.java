/* Listing 2-3: A program that uses the scanner class.
   This program will get an input from the user
   and then print that input back out to them. */

import java.util.Scanner;

public class ScannerApp
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		System.out.print("Enter an integer: ");
		int x = sc.nextInt();
		System.out.println("You entered " + x + ".");
	}
}