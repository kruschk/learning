/* This application displays a hello message on
   the console by creating an instance of the
   Greeter class and then calling the Greeter
   object's sayHello method. */

public class HelloApp2
{
	public static void main(String[] args)
	{
		Greeter myGreeterObject = new Greeter();
		myGreeterObject.sayHello();
		myGreeterObject.sayHelloMsgBox();
	}
}