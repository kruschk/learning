// Example of a while loop that aborts when it reaches 12.

public class Dodecaphobia
{
	public static void main(String[] args)
	{
		int number = 2;
		while (number <= 20)
		{
			if (number == 12)
				break;
			System.out.print(number + " ");
			number += 2;
		}
		System.out.println();
	}
}