// Swallowing exceptions, but not being lazy about it.

import java.io.*;

public class FileException6
{
	public static void main(String[] args)
	{
		openFile("C:\\test.txt"));
	}
	
	public static boolean openFile(String name)
	{
		boolean fileOpened = false;
		try
		{
			FileInputStream f = new FileInputStream(name);
			fileOpened = true;
		}
		catch (FileNotFoundException e)
		{
		}
		return fileOpened;
	}
}