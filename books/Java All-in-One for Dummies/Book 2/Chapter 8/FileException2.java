// Catching FileNotFoundException.

import java.io.*;

public class FileException2
{
	public static void main(String[] args)
	{
		openFile("C:\\test.txt");
	}
	
	public static void openFile(String name)
	{
		try
		{
			FileInputStream f = new FileInputStream(name);
		}
		catch (FileNotFoundException e)
		{
			System.out.println("File not found.");
		}
	}
}