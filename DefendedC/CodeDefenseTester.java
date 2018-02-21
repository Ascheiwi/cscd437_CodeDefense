import java.util.*;
import java.io.*;
import java.net.URL;
public class CodeDefenseTester 
{
	private static Scanner kb = new Scanner(System.in);
	
	public static void main(String...args)
	{
		File inputFile;
		File outputFile;
		
		promptName();
		promptNumbers();
		inputFile = promptInputFile();
		outputFile = promptOutputFile();
		promptPassword();
	}
	
	public static void promptName()
	{
		String uncheckedName; 
		boolean properlyEntered1 = false;
		boolean properlyEntered2 = false;
		
		while(properlyEntered1 == false)
		{
			System.out.println("Please enter a first name (less than 50 characters): ");
			uncheckedName = kb.nextLine();
			if(checkName(uncheckedName))
			{
				properlyEntered1 = true;
			}
		}
		
		while(properlyEntered2 == false)
		{
			System.out.println("Pleas enter a last name (less than 50 characters): ");
			uncheckedName = kb.nextLine();
				if(checkName(uncheckedName))
				{
					properlyEntered2 = true;
				}
		}
	}
	
	public static void promptNumbers()
	{
		String numOne, numTwo;
		boolean properNumber = false;
		
		while(properNumber == false)
		{
			System.out.println("Please enter first integer (Only digits, -2147483648 to 2147483648): ");
			numOne = kb.nextLine();
			if(checkNumber(numOne))
			{
				properNumber = true;
			}
		}
		properNumber = false;
		while(properNumber == false)
		{
			System.out.println("Please enter second integer (Only digits, -2147483648 to 2147483648): ");
			numTwo = kb.nextLine();
			if(checkNumber(numTwo))
			{
				properNumber = true;
			}
		}
	}
	
	public static File promptInputFile()
	{
		String fileName = "";
		boolean properFile = false;
		
		while(properFile == false)
		{
			System.out.println("Please enter input file (must be in the same directory as this program): ");
			fileName = kb.nextLine();
			if(checkFile(fileName))
			{
				properFile = true;
			}
		}
		URL path = Tester.class.getResource(fileName);
		File inputFile = new File(path.getFile());
		return inputFile;
	}
	
	public static File promptOutputFile()
	{
		String fileName = "";
		boolean properFile = false;
		
		while(properFile == false)
		{
			System.out.println("Please enter output file (must be in the same directory as this program): ");
			fileName = kb.nextLine();
			if(checkFile(fileName))
			{
				properFile = true;
			}
		}
		URL path = Tester.class.getResource(fileName);
		File outputFile = new File(path.getFile());
		return outputFile;
	}
	
	public static void promptPassword()
	{
		String password;
		boolean properPassword = false;
		
		while(properPassword == false)
		{
			System.out.println("Please enter a password: ");
			password = kb.nextLine();
			if(checkPassword(password))
			{
				properPassword = true;
			}
		}
	}
	
	public static boolean checkName(String name)
	{
		if(name.matches("[a-zA-Z'.]{1,50}"))
		{
			return true;
		}
		System.out.println("That is not a valid name.");
		return false;
	}
	
	public static boolean checkNumber(String num)
	{
		
		if(num.matches("^-*[0-9,.]+$"))
		{
			int number = Integer.parseInt(num);
			if(number > -2147483647 && number < 2147483647)
			{
				return true;
			}
		}
		System.out.println("That is not a valid int.");
		return false;
	}
	
	public static boolean checkFile(String fileName)
	{
		URL path = Tester.class.getResource(fileName);
		try
		{
			File file = new File(path.getFile());
			return true;
		}
		catch(Exception e)
		{
			System.out.println("That is not a valid file.");
			return false;
		}
		
	}

	
	public static boolean checkPassword(String pass)
	{
		if(pass.matches(arg0))
	}
	
	
	
}
