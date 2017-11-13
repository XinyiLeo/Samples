package Project;

import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class librarian {
	
	private static final String DB_ID = "jdbc:oracle:thin:@db12.cse.cuhk.edu.hk:1521:db12";
	private static final String User_Name = "c046";
	private static final String Password = "atfosiji";
	
	public static void operations(){
		System.out.println("-----Operations for librarian menu-----");
		System.out.println("What kinds of operation would you like to perform?");
		System.out.println("1. Book Borrowing");
		System.out.println("2. Book Returning");
		System.out.println("3. Return to the main menu");
		System.out.print("Enter Your Choice: ");
		return;
	}
	
	public static void borrowBook(String userID, int callNum, int copyNum) throws SQLException{
		DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		Date date = new Date(System.currentTimeMillis());
		
		//Need to make sure date is formatted correctly
		//Need to make sure time is in Hong Kong format
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		stmt.execute("INSERT INTO Checked_out_Records "
				+ "(Call_Number, Copy_Number, User_ID, Check_Out_Date)"
				+ "VALUES ('"+callNum+"',"+copyNum+",'"+userID+"','"+date+"'");
		stmt.execute("UPDATE Book_Copy SET checkedOut = TRUE WHERE Call_Number = '"+callNum+"' ;");
		//check to see if the book is available by callNum and copyNum
		//Return statement about the book being available
		//update check out record with userID, callNum, copyNum
		//update bookcopy record, with number of books and checked out
		//print statements about validity of the function
		
		conn.close();
		stmt.close();
	}
	//borrow book function
	//updates the database
	//displays a message
	
	
	//return book function
	//updates the database
	//displays a message
	public static void returnBook(String userID, int callNum, int copyNum) throws SQLException{
		
		//send query to see if the checkout table has the record
		//I can parse the records for the userID that I'm looking for if the return date is null
		//Perhaps I can get the query to send just the boolean value
		//send message that the check out record is there
		//update the database with the return date of the book
		//output a message to confirm the function.
		DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		Date date = new Date(System.currentTimeMillis());
		
		//Need to make sure date is formatted correctly
		//Need to make sure time is in Hong Kong format
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		stmt.execute("UPDATE Checked_Out_Records SET Return_Date = '"+date+"' "
				+ "WHERE Call_Number = '"+callNum+"', Copy_Number = '"+copyNum+"', User_ID = '"+userID+"';");
		stmt.execute("UPDATE Book_Copy SET checkedOut = FALSE "
				+ "WHERE Call_Number = '"+callNum+"', Copy_Number = '"+copyNum+"' ;");
				
		conn.close();
		stmt.close();
	}
}
