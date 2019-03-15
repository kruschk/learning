/* Catching multiple exceptions with two different forms of try-catch that do
   the same thing. */

import java.io.*;
import java.util.*;

public class CatchMultiple
{
	public static void main(String[] args)
	{
		System.out.println(catchLong());
		System.out.print(catchConcise());
	}
	
	public static String catchLong()
	{
		try
		{
			return "No issues"; // Statements that might throw FileNotFoundException or IOException
		}
		catch (FileNotFoundException e)
		{
			return e.getMessage();
		}
		catch (IOException e)
		{
			return e.getMessage();
		}
	}

	public static String catchConcise()
	{
		try
		{
			return "No issues here, either"; // Statements that might throw FileNotFoundException or IOException
		}
		catch (FileNotFoundException | InputMismatchException e)
		{
			return e.getMessage();
		}
	}
}