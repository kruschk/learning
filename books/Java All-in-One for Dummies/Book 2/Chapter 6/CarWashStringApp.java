// Listing 6-4: A versioin of the car wash program that prevents nasty falls.

import java.util.Scanner;

public class CarWashStringApp
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		System.out.println("The Car Wash Application!\n\n");
		System.out.print("Enter the package code: ");
		String s = sc.next();
		
		String details = "";
		
		switch (s.toUpperCase())
		{
			case "PRESIDENTIAL":
				details = packageE() + packageD() + packageC() + packageB()
					+ packageA();
				break;
			case "ELITE":
				details = packageD() + packageC() + packageB() + packageA();
				break;
			case "DELUXE":
				details = packageC() + packageB() + packageA();
				break;
			case "SUPER":
				details = packageB() + packageA();
				break;
			case "STANDARD":
				details = packageA();
				break;
			default:
				details = "That's not one of the codes.";
				break;
		}
		System.out.println("\nThat package includes:\n");
		System.out.print(details);
	}
	
	public static String packageA()
	{
		return "\tWash, Vacuum, and Hand Dry.\n";
	}
	
	public static String packageB()
	{
		return "\tWax, plus... \n";
	}
	
	public static String packageC()
	{
		return "\tLeather/Vinyl Treatment, plus... \n";
	}
	
	public static String packageD()
	{
		return "\tTire Treatment, plus...\n";
	}
	
	public static String packageE()
	{
		return "\tNew Car Scent, plus...\n";
	}
}