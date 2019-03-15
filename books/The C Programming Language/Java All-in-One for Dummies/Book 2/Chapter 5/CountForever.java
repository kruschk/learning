/* This script uses an infinite while loop to count even numbers until the
   user closes the program or it experiences an overflow. */
   
public class CountForever
{
	public static void main(String[] args)
	{
		int number = 2;
		while (true)
		{
			System.out.print(number + " ");
			number += 2;
		}
	}
}