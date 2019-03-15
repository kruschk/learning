// Listing 6-1: The else-if version of a voting machine errorCodeor decoder.

import java.util.Scanner;

public class VoterApp
{
	static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args)
	{
		System.out.println
			("Welcome to the voting machine error code decoder.\n\nIf your "
			+ "voting machine generates an error code,\nyou can use this "
			+ "program to determine the exact\ncause of the error.\n");
		System.out.print("Enter the error code: ");
		int errorCode = sc.nextInt();
		
		String msg;
		if (errorCode == 1)
			msg = "Voter marked more than one cadidate.\nBallot rejected.";
		else if (errorCode == 2)
			msg = "Box checked and write-in candidate entered.\nBallot rejected.";
		else if (errorCode == 3)
			msg = "Entire ballot was blank.\nBallot filled in according to secret plan.";
		else if (errorCode == 4)
			msg = "Nothing unusual about the ballot.\nVoter randomly selected for tax audit.";
		else if (errorCode == 5)
			msg = "Voter filled in every box.\nBallot counted twice.";
		else if (errorCode == 6)
			msg = "Voter drooled in voting machine.\nBeginning spin cycle.";
		else if (errorCode == 7)
			msg = "Voter lied to pollster after voting.\nVoter's ballot changed to match polling data.";
		else
			msg = "Voter filled out ballot correctly.\nBallot discarded anyway.";
		System.out.println(msg);
	}
}