/* This class creates a Greeter object
   that displays a hello message on
   the console and in a message box. */

import javax.swing.JOptionPane;   

public class Greeter
{
	public void sayHello()
	{
		System.out.println("Hello, world!");
	}
	public void sayHelloMsgBox()
	{
		JOptionPane.showMessageDialog(null, "Hello, world!", "GreeterMsgBox", JOptionPane.INFORMATION_MESSAGE);
	}
}