/* Listing 2-4: A program that uses the JOptionPane class to get user input.
   This program will get an input from the user using the JOptionPane class
   and then print that input back out to them. */

import javax.swing.JOptionPane;

public class DialogApp
{
	public static void main(String[] args)
	{
		String s;
		s = JOptionPane.showInputDialog("Enter an integer: ");
		int x = Integer.parseInt(s);
		System.out.println("You entered " + x + ".");
	}
}