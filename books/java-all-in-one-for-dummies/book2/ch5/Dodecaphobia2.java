// Example of an infinite while loop that aborts when it reaches 12.

public class Dodecaphobia2
{
	public static void main(String[] args)
	{
		int number = 2;
		while (true)
		{
			if (number == 12)
				break;
			System.out.print(number + " ");
			number += 2;
		}
		System.out.println();
	}
}