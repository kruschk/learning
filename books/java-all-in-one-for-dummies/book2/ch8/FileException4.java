// Throws FileNotFoundException to main, which also throws the exception (causing abrupt termination).

import java.io.*;

public class FileException4
{
	public static void main(String[] args)
		throws FileNotFoundException
	{
		openFile("C:\\test.txt");
	}
	
	public static void openFile(String name)
		throws FileNotFoundException			// If more than one exception is needed, list them like so: throws FileNotFoundException, IOException, etc.
	{
		FileInputStream f = new FileInputStream(name);
	}
}