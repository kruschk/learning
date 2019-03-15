/* Uses a while loop to print the even numbers from 2 through 20 on the
   console. */

public class EvenCounter
{
	public static void main(String[] args)
	{
		int number = 2;
		while (number <= 20)
		{
			System.out.print(number + " ");
			number += 2;
		}
		System.out.println();
	}
}