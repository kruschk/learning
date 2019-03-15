/* Listing 3-4: Rolling the dice.
   Note the rounding function on lines 19-23 */

public class DiceApp
{
	public static void main(String[] args)
	{
		int roll;
		String msg = "Here are 100 random rolls of the dice:";
		System.out.println(msg);
		for (int i = 0; i < 100; i++)
		{
			roll = randomInt(1, 6);
			System.out.print(roll + " " );
		}
		System.out.println();
	}
	
	public static int randomInt(int low, int high)
	{
		int result = (int)(Math.random() * (high - low + 1)) + low;
		return result;
	}
}