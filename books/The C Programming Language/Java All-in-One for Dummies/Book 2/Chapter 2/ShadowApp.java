/* Listing 2-2: A class that demonstrates shadowing.
   This script will help to clarify the concept of shadowed variables.
   Shadowing is a common source of errors, and should generally be avoided! */

public class ShadowApp
{
	static int x; // Class variable x is declared as an integer.
	
	public static void main(String[] args)
	{
		x = 5; // Class variable x is assigned a value of 5.
		System.out.println("x = " + x); // Prints x = 5.
		double x; // Local variable x is declared as a double.
		x = 10.0; // Local variable x is initialized.
		System.out.println("x = " + x); // Prints x = 10.0.
		System.out.println("ShadowApp.x = " + ShadowApp.x); // Prints ShadowApp.x = 5.
		// ShadowApp.x allows you to call the shadowed class variable, x.
	}
}