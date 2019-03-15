// Tic-Tac-Toe game

import java.util.Scanner;

public class TicTacToe
{
	static Scanner sc = new Scanner(System.in);
	static int A1, A2, A3, B1, B2, B3, C1, C2, C3;
	
	public static void main(String[] args)
	{
		System.out.print("Welcome to Tic-Tac-Toe. Please enter your first move: ");
		String playerChoice = sc.nextLine();
		convert(playerChoice);
		printBoard();
		checkWinner();
	}
	
	public static void printBoard()
	{
		System.out.println(" " + A1 + " | " + B1 + " | " + C1);
		System.out.println("---|---|---");
		System.out.println(" " + A2 + " | " + B2 + " | " + C2);
		System.out.println("---|---|---");
		System.out.println(" " + A3 + " | " + B3 + " | " + C3);
	}
	
	public static void convert(String playerChoice)
	{
		
		if (playerChoice.equalsIgnoreCase("A1"))
			A1 = 1;
		else if (playerChoice.equalsIgnoreCase("A2"))
			A2 = 1;
		else if (playerChoice.equalsIgnoreCase("A3"))
			A3 = 1;
		else if (playerChoice.equalsIgnoreCase("B1"))
			B1 = 1;
		else if (playerChoice.equalsIgnoreCase("B2"))
			B2 = 1;
		else if (playerChoice.equalsIgnoreCase("B3"))
			B3 = 1;
		else if (playerChoice.equalsIgnoreCase("C1"))
			C1 = 1;
		else if (playerChoice.equalsIgnoreCase("C2"))
			C2 = 1;
		else if (playerChoice.equalsIgnoreCase("C3"))
			C3 = 1;
		else
		{
			System.out.print("Invalid input! Try again: ");
			playerChoice = sc.nextLine();
			convert(playerChoice);
			System.out.println();
		}
	}
	
	public static void checkWinner()
	{
		if    ((A1 == 1 && A2 == 1 && A3 == 1) || (B1 == 1 && B2 == 1 && B3 == 1)
			|| (C1 == 1 && C2 == 1 && C3 == 1) || (A1 == 1 && B1 == 1 && C1 == 1)
			|| (A2 == 1 && B2 == 1 && C2 == 1) || (A3 == 1 && B3 == 1 && C3 == 1)
			|| (A1 == 1 && B2 == 1 && C3 == 1) || (A3 == 1 && B2 == 1 && C1 == 1))
		{
			System.out.println("Player wins!");
		}
	}
}