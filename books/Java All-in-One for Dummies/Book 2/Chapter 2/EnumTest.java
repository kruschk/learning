/* Defines an enum, creates a variable of the enum's type, assigns a value, and
   prints the result. */

public class EnumTest
{
	public enum CardSuit {HEARTS, SPADES, CLUBS, DIAMONDS}
	
	public static void main(String[] args)
	{
		CardSuit suit;
		suit = CardSuit.HEARTS;
		System.out.println("The suit is " + suit);
	}
}