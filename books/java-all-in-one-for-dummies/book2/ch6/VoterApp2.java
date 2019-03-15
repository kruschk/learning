// Listing 6-2: The switch version of a voting machine error decoder.

import java.util.Scanner;

public class VoterApp2
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
		
		switch (errorCode)
		{
			case 1:
				msg = "Voter marked more than one cadidate.\nBallot rejected.";
				break;
			case 2:
				msg = "Box checked and write-in candidate entered.\n"
				+ "Ballot rejected.";
				break;
			case 3:
				msg = "Entire ballot was blank.\nBallot filled in according to "
				+ "secret plan.";
				break;
			case 4:
				msg = "Nothing unusual about the ballot.\nVoter randomly "
				+ "selected for tax audit.";
				break;
			case 5:
				msg = "Voter filled in every box.\nBallot counted twice.";
				break;
			case 6:
				msg = "Voter drooled in voting machine.\nBeginning spin "
				+ "cycle.";
				break;
			case 7:
				msg = "Voter lied to pollster after voting.\nVoter's ballot "
				+ "changed to match polling data.";
				break;
			default:
				msg = "Voter filled out ballot correctly.\nBallot discarded "
				+ "anyway.";
				break;
		}
		System.out.println(msg);
	}
}