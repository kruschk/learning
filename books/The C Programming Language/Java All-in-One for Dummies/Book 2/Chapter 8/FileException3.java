// Throws FileNotFoundException to main, which catches the exception.

import java.io.*;

public class FileException3
{
	public static void main(String[] args)
	{
		try
		{
			openFile("C:\\test.txt");
		}
		catch (FileNotFoundException e)
		{
			System.out.println("File not found.");
		}
	}
	
	public static void openFile(String name)
		throws FileNotFoundException			// If more than one exception is needed, list them like so: throws FileNotFoundException, IOException, etc.
	{
		FileInputStream f = new FileInputStream(name);
	}
}