/* Listing 3-6: A program that uses the NumberFormat class variable. */

import java.text.NumberFormat;

public class NumberFormatClassApp
{
	static NumberFormat cf = NumberFormat.getCurrencyInstance();
	
	public static void main(String[] args)
	{
		printMyAllowance();
		printCostOfPaintballGun();
	}
	
	public static void printMyAllowance()
	{
		double myAllowance = 5.000005;
		System.out.println("My allowance: " + cf.format
		System.out.println("My allowance: " + NumberFormat.getCurrencyInstance().format(myAllowance));
	}
	
	public static void printCostOfPaintballGun()
	{
		double costOfPaintballGun = 69.950;
		System.out.println("Cost of paintball gun: " + cf.format(costOfPaintballGun));
	}
}