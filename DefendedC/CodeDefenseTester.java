import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.util.*;
import java.io.*;
import java.math.BigInteger;
import java.net.URL;
import java.nio.file.Files;

import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
public class CodeDefenseTester 
{
	private static Scanner kb = new Scanner(System.in);
	
	public static void main(String...args) throws IOException
	{
		File[] files = new File[2];
		
		String[] name = promptName();
		int[] ints = promptNumbers();
		files[0] = promptInputFile();
		files[1] = promptOutputFile(files);
		promptPassword();
		Output(name,ints,files);
	}
	
	private static void Output(String[] name, int[] ints, File[] files) throws IOException
	{
		String str;
		BigInteger sum, multiplied;
		BigInteger[] bigInts = new BigInteger[2];
		bigInts[0] = BigInteger.valueOf(ints[0]);
		bigInts[1] = BigInteger.valueOf(ints[1]);
		PrintWriter fout = new PrintWriter(new FileWriter(files[1]));
		fout.println(name[0] + " " + name[1]);
		try{
			sum = bigInts[0].add(bigInts[1]);

			fout.println(sum + " ints added together");

		}
		catch(ArithmeticException e)
		{
			sum = BigInteger.valueOf(0);
			fout.println("sum was to large");
		}
		
		try
		{
			multiplied = bigInts[0].multiply(bigInts[1]);
			fout.println(multiplied + " ints multiplied together");
		}
		catch(ArithmeticException e)
		{
			multiplied = BigInteger.valueOf(0);
			fout.println("multiplied together ints were to large");
		}
		
		BufferedReader bufferedReader = new BufferedReader(new FileReader(files[0]));
		while((str = bufferedReader.readLine()) != null) {
            fout.println(str);
        }  
		fout.close();
		bufferedReader.close();

		
		
	}

	public static String[] promptName()
	{
		String name1 = null,name2 = null; 
		boolean properlyEntered1 = false;
		boolean properlyEntered2 = false;
		
		while(properlyEntered1 == false)
		{
			System.out.println("Please enter a first name (less than 50 characters): ");
			name1 = kb.nextLine();
			if(checkName(name1))
			{
				properlyEntered1 = true;
			}
		}
		
		while(properlyEntered2 == false)
		{
			System.out.println("Pleas enter a last name (less than 50 characters): ");
			name2 = kb.nextLine();
				if(checkName(name2))
				{
					properlyEntered2 = true;
				}
		}
		String[] names= new String[2];
		names[0] = name1; names[1] = name2;
		return names;
	}
	
	public static int[] promptNumbers()
	{
		String numOne = null, numTwo = null;
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
		int[] ints = new int[2];
		ints[0] = Integer.parseInt(numOne); ints[1] = Integer.parseInt(numTwo);
		return ints;
		
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
		//URL path = CodeDefenseTester.class.getResource(fileName);
		File inputFile = new File(fileName);
		return inputFile;
	}
	
	public static File promptOutputFile(File[] files)
	{
		String fileName = "";
		boolean properFile = false;
		
		while(properFile == false)
		{
			System.out.println("Please enter output file (must be in the same directory as this program): ");
			fileName = kb.nextLine();
			if(files[0].compareTo(new File(fileName)) != 0)
			{
				properFile = true;
			}
			else
			{
				if(files[0].compareTo(new File(fileName)) != 0)
					System.out.println("output file cannot be the same as the output file");
			}
		}
		//URL path = CodeDefenseTester.class.getResource(fileName);
		File outputFile = new File(fileName);
		return outputFile;
	}
	
	public static void promptPassword() throws IOException
	{
		byte[] hashed;
		File fout = new File("pass_salt.txt");
		FileOutputStream fos = new FileOutputStream(fout);
		Random RANDOM = new SecureRandom();
		String password = null;
		char[] pass;
		boolean properPassword = false, isCorrect = false;
		
		while(properPassword == false)
		{
			System.out.println("Please enter a password(8-50 characters long): ");
			password = kb.nextLine();
			if(checkPassword(password))
			{
				properPassword = true;
			}
		}
		properPassword = false;
		byte[] salt = new byte[16];
		pass = password.toCharArray();
		RANDOM.nextBytes(salt);
		fos.write(hash(pass,salt));
		fos.write('\t');
		fos.write(salt);
		salt = null;
		fos.close();
		while(isCorrect == false)
		{
			while(properPassword == false)
			{
				System.out.println("Please enter a password(8-50 characters long): ");
				password = kb.nextLine();
				if(checkPassword(password))
				{
					properPassword = true;
				}
			}
			pass = password.toCharArray();
			File fin = new File("pass_salt.txt");
			salt = Files.readAllBytes(fin.toPath());
			hashed = Arrays.copyOfRange(salt, 0, 32);
			salt = Arrays.copyOfRange(salt,33,49);
			
			if(isExpectedPassword(pass,salt,hashed))
			{
				isCorrect = true;
				System.out.println("Password is correct");
			}
			else
			{
				System.out.println("Incorrect password please try again");
				properPassword = false;
			}

		}
		
		
	}
	
	public static byte[] hash(char[] pass, byte[] salt)//https://stackoverflow.com/questions/18142745/how-do-i-generate-a-salt-in-java-for-salted-hash
	{
		PBEKeySpec spec = new PBEKeySpec(pass, salt, 1000, 256);
	    Arrays.fill(pass, Character.MIN_VALUE);
	    try {
	    	SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
	    	return skf.generateSecret(spec).getEncoded();
	    } catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
	    	throw new AssertionError("Error while hashing a password: " + e.getMessage(), e);
	    } finally {
	    	spec.clearPassword();
	    }
	}
	
	public static boolean isExpectedPassword(char[] password, byte[] salt, byte[] expectedHash) {//https://stackoverflow.com/questions/18142745/how-do-i-generate-a-salt-in-java-for-salted-hash
	    byte[] pwdHash = hash(password, salt);
	    Arrays.fill(password, Character.MIN_VALUE);
	    if (pwdHash.length != expectedHash.length) return false;
	    for (int i = 0; i < pwdHash.length; i++) {
	      if (pwdHash[i] != expectedHash[i]) return false;
	    }
	    return true;
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
		int number = 0;
		if(num.matches("^-*[0-9,.]+$"))//"^-*[0-9,.]+$"
		{
			try{
				number = Integer.parseInt(num);
			}
			catch(NumberFormatException e)
			{
				System.out.println("That is not a valid int.");
				return false;
				
			}
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
		URL path = CodeDefenseTester.class.getResource(fileName);
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
		if(pass.length() < 50 && pass.length() > 8)
			return true;
		else return false;
	}
	
	
	
}