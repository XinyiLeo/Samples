package Project;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class librarianDir {
	private static final String DB_ID = "jdbc:oracle:thin:@db12.cse.cuhk.edu.hk:1521:db12";
	private static final String User_Name = "c046";
	private static final String Password = "atfosiji";
	
	public static void operations(){
		System.out.println("-----Operations for library director menu-----");
		System.out.println("What kinds of operations would you like to perform?");
		System.out.println("1. List all un-related book copies which are checked-out within a period");
		System.out.println("Return to the main menu");
		System.out.print("Enter Your Choice: ");
		return;
	}
	
	public static void checkedOutBooks(String fromDate, String toDate) throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		ResultSet rs = null;
		try {
			rs = stmt.executeQuery("SELECT U.User_ID, C.Call_Number, C.Copy_Number, C.Check_out_Date"
					+ " FROM Library_Users AS U, "
					+ "Checked_Out_Records AS C "
					+ "WHERE U.User_ID = C.User_ID "
					+ "AND C.Check_out_Date >= '"+fromDate+"' "
					+ "AND C.Check_out_Date <= '"+toDate+"' "
					+ "ORDER BY C.Check_out_Date DESC;");
			System.out.println("List of UnReturned Books:");
			System.out.println("|LibUID|CallNum|CopyNum|Checkout|");
			while(rs.next()){
				System.out.println("|"+rs.getString(0)+"|"+rs.getString(1)+"|"+rs.getLong(2)+"|"+rs.getString(3));
			}
			System.out.println("End of Query.");
		} catch (SQLException e) {
			System.err.println("Error while executing search query.");
		}
		rs.close();
		conn.close();
		stmt.close();
	}
}
