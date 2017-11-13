package Project;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class libraryUser {
	
	private static final String DB_ID = "jdbc:oracle:thin:@db12.cse.cuhk.edu.hk:1521:db12";
	private static final String User_Name = "c046";
	private static final String Password = "atfosiji";
	
	public static void operations(){
		System.out.println("-----Operations for library user menu-----");
		System.out.println("What kinds of operations would you like to perform?");
		System.out.println("1. Search for Books");
		System.out.println("2. Show load record of a user");
		System.out.println("3. Return to the main menu");
		System.out.print("Enter Your Choice: ");
		return;
	}
	public static void searchOperations(){
		System.out.println("Choose the Search criterion: ");
		System.out.println("1. call number");
		System.out.println("2. title");
		System.out.println("3. author");
		System.out.print("Choose the search criterion: ");
		return;
	}
	//search for books functions
	//by call number
	//by title
	//by author
	public static void searchBooksCallNumber(String callNum) throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		//The part of the statement which is indented is the sub-query.
		ResultSet rs = stmt.executeQuery("SELECT B.Call_Number, B.Title, B.Author, "
				+ "(SELECT Number_of_Copies "
				+ "FROM Books WHERE Call_Number = '"+callNum+"')"
				+ "- ( SELECT COUNT(*) FROM Checked_Out_Records"
				+ " WHERE Call_Number = '"+callNum+"' "
				+ "AND Return_Date IS null)  AS AvailableCopies "
				+ "FROM Books AS B "
				+ "WHERE B.Call_Number = '"+callNum+"' "
				+ "ORDER BY B.Call_Number;");
		while(rs.next()){
			System.out.println("Call Number: " + rs.getString(0));
			System.out.println("Title: " + rs.getString(1));
			System.out.println("Author: " + rs.getString(2));
			System.out.println("Available Copies: " + rs.getString(3));
		}
		rs.close();
		conn.close();
		stmt.close();
	}
	public static void searchBooksTitle(String title) throws SQLException{
		//this requires partial matching
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();

		//This query has not been tested
		ResultSet rs = stmt.executeQuery("SELECT Call_Number AS CN, Title, Author,"
				+ "(SELECT Number_of_Copies FROM Books WHERE Call_Number = CN)"
				+ "-(SELECT COUNT(*) FROM Checked_Out_Records WHERE Call_Number = CN "
				+ "AND Return_Date IS null) AS AvailablCopies"
				+ "FROM Books AS B WHERE B.Title = '"+title+""
				+ "' ORDER BY B.Call_Number;");
		while(rs.next()){
			System.out.println("Call Number: " + rs.getString(0));
			System.out.println("Title: " + rs.getString(1));
			System.out.println("Author: " + rs.getString(2));
			System.out.println("Available Copies: " + rs.getString(3));
		}
		rs.close();
		conn.close();
		stmt.close();
	}
	public static void searchBooksAuthor(String author) throws SQLException{
		//this required partial matching this will be easier with the authors table
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();

		//This query has not been tested
		ResultSet rs = stmt.executeQuery("SELECT Call_Number AS CN, Title, Author, "
				+ "(SELECT Number_of_Copies FROM Books WHERE Call_Number = CN)"
				+ "-(SELECT COUNT(*) FROM Checked_Out_Records WHERE Call_Number = CN "
				+ "AND Return_Date IS null) AS AvailablCopies"
				+ "FROM Books AS B WHERE B.Author = '"+author+""
				+ "' ORDER BY B.Call_Number;");
		while(rs.next()){
			System.out.println("Call Number: " + rs.getString(0));
			System.out.println("Title: " + rs.getString(1));
			System.out.println("Author: " + rs.getString(2));
			System.out.println("Available Copies: " + rs.getString(3));
		}
		rs.close();
		conn.close();
		stmt.close();
	}
	//return details about user
	//takes in user ID
	//shows values about a user
	public static void userRecord(String userID) throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		ResultSet rs = null;
		try {
			rs = stmt.executeQuery("SELECT C.Call_Number, C.Copy_Number, B.Title, B.Author, C.Check_out_Date, C.Return_Date"
					+ "FROM Checked_Out_Records as C, Books as B "
					+ "WHERE B.Call_Number = C.Call_number AND C.User_ID = '"+userID+"'"
					+ " AND '"+userID+"' IN (SELECT User_ID FROM Library_Users);");
		} catch (SQLException e) {
			System.err.println("Unfortunately there was an error while processing your request.");
		}
		while(rs.next()){
			System.out.println("Records: Call Number = "+rs.getString(0)+" Copy Number= "+rs.getString(1)
			+" Title= "+rs.getString(2)+" Author= "+rs.getString(3)+" Check out Date= "
			+rs.getString(4)+"Return Date = "+rs.getString(5));
		}
		rs.close();
		stmt.close();
		conn.close();
	}
}
