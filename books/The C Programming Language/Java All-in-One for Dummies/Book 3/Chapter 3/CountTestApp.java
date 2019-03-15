// Listing 3-1: The CountTest Application.

public class CountTestApp
{
	public static void main(String[] args)
	{
		printCount();
		for (int i = 0; i < 10; i++)
		{
			CountTest cl = new CountTest();
			printCount();
		}
	}
	
	private static void printCount()
	{
		System.out.println("There are now " + CountTest.getInstanceCount() + " instances of the countTest class.");
	}
}

class CountTest
{
	private static int instanceCount = 0;
	
	public CountTest()
	{
		instanceCount++;
	}
	
	public static int getInstanceCount()
	{
		return instanceCount;
	}
}