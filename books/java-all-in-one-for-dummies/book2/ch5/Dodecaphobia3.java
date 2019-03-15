// Example of a while loop that aborts when it reaches 12.

public class Dodecaphobia3
{
	public static void main(String[] args)
	{
		int number = 0;
		while (number < 20)
		{
			number += 2;
			if (number == 12)
			{
				System.out.print("Ahh! ");
				continue;
			}
			System.out.print(number + " ");
		}
		System.out.println();
	}
}