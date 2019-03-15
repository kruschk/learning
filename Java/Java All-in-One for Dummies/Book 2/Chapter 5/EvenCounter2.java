// Similar to EvenCounter, but uses a do-while loop instead of a while loop.

public class EvenCounter2
{
	public static void main(String[] args)
	{
		int number = 2;
		do
		{
			System.out.print(number + " ");
			number += 2;
		} while (number <= 20);
		
		System.out.println();
	}
}