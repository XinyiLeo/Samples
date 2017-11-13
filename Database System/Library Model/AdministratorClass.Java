package Project;

import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;
//import java.sql*;

public class administrator {
	private static final String DB_ID = "jdbc:oracle:thin:@db12.cse.cuhk.edu.hk:1521:db12";
	private static final String User_Name = "c046";
	private static final String Password = "atfosiji";
	//private Connection conn = null;
	//private Statement stmt = null;
	//private ResultSet rs = null;

	public static void operations(){
		System.out.println("\n" + "-----Operations for administrator menu-----");
		System.out.println("What kinds of operations would you like to perform?");
		System.out.println("1. Create all tables");
		System.out.println("2. Delete all tables");
		System.out.println("3. Load from datafile");
		System.out.println("4. Show number of records in each table");
		System.out.println("5. Return to the main menu");
		System.out.print("Enter Your Choice: ");
		return;
	}
	/*function to create all tables
	 *Implements the schema that we have designed previously
	 *Do not create the tables multiple times
	 *This should be hard coded so that our database schema can't be changed
	 *I should not have options to create my own schema on the fly as this 
	 *won't let me maintain the structure I've coded when adding data
	 */
	public static void createTables() throws SQLException{
		
		System.out.println("Creating new tables");	
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		
		System.out.println("Creating categories tables...");
		
		stmt.executeUpdate("CREATE TABLE Categories" +
				"(Category_ID INTEGER not NULL," +
				"Max_Books INTEGER not NULL," +
				"Loan_Period INTEGER not NULL," +
				"PRIMARY KEY ( Category_ID ))");
		
		System.out.println("Categories table created.");
		System.out.println("Creating Library_Users table...");
		
		stmt.execute("CREATE TABLE Library_Users("
				+ "User_ID VARCHAR(10) not NULL,"
				+ "Name VARCHAR(25) not NULL,"
				+ "Address VARCHAR(100) not NULL,"
				+ "Category_ID INTEGER not NULL,"
				+ "PRIMARY KEY (User_ID),"
				+ "FOREIGN KEY(Category_ID) REFERENCES Categories)");
				//+ "ON DELETE NO ACTION)");
		
		System.out.println("Library_Users table created");
		
		stmt.execute("CREATE TABLE Book_Copies("
				+ "Call_Number VARCHAR(8) not NULL, "
				+ "Copy_Number INTEGER not NULL,  "
				+ "CheckOut_Record NUMBER(1),"
				+ "PRIMARY KEY (Call_Number, Copy_Number))");

		System.out.println("Book_Copies table created");
		
		stmt.execute("CREATE TABLE Authors("
				+ "Author VARCHAR(25) not NULL,"
				+ "Title VARCHAR(30) not NULL,"
				+ "PRIMARY KEY (Author, Title))");
		
		System.out.println("Authors table created");

		stmt.execute("CREATE TABLE Books( "
				+ "Call_Number VARCHAR(8) not NULL,"
				+ "Number_of_Copies INTEGER not NULL,"
				+ "Title VARCHAR(30) not NULL, "
				+ "Author VARCHAR(25) not NULL,"
				+ "Date_of_Publication DATE not NULL, "
				+ "PRIMARY KEY (Call_Number),"
				+ "FOREIGN KEY (Author, Title) REFERENCES Authors"
				+ " ON DELETE CASCADE)");

		System.out.println("Books table created");
		
		stmt.execute("CREATE TABLE Checked_Out_Records("
				+ "Call_Number VARCHAR(8) not NULL,"
				+ "Copy_Number INTEGER not NULL,"
				+ "User_ID VARCHAR(10) not NULL, "
				+ "Check_out_Date DATE  not NULL, "
				+ "Return_Date DATE, "
				+ "PRIMARY KEY (Call_Number, Copy_Number, User_ID,"
				+ "Check_out_Date),"
				+ "FOREIGN KEY (Call_Number) REFERENCES Books, "
				//+ "ON DELETE NO ACTION, "
				+ "FOREIGN KEY (Call_Number, Copy_Number) REFERENCES Book_Copies, "
				//+ "ON DELETE NO ACTION, "
				+ "FOREIGN KEY (User_ID) REFERENCES Library_Users)");
				//+ " ON DELETE NO ACTION )");
		
		System.out.println("Check_Out_Record table created");
		
		conn.close();
		stmt.close();
		System.out.println("Tables created.");
	}

	/*function to delete all tables
	 *Deletes the table schema in the database
	 *Warning option to stop users from deleting things without a check
	 *Message to confirm the action
	 */
	public static void deleteTables() throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		System.out.println("Are you sure you want to delete ALL tables?");
		System.out.println("If so press shift + y   ( Y )");
		Scanner scc = new Scanner(System.in);
		String userInput = scc.nextLine();
		if(userInput.equals("Y")){
			
			stmt.execute("DROP TABLE Checked_Out_Records");
			System.out.println("Checked out records delete");
			
			stmt.execute("DROP TABLE Books");
			System.out.println("Books Deleted");
			
			stmt.execute("DROP TABLE Authors");
			System.out.println("Authors Deleted");
			
			stmt.execute("DROP TABLE Book_Copies");
			System.out.println("Book Copies Deleted");
			
			stmt.execute("DROP TABLE Library_Users");
			System.out.println("Library Users Deleted");
			
			stmt.execute("DROP TABLE Categories");
			System.out.println("Categories Deleted");
			
			System.out.println("All tables were deleted (Dropped).");
		}
		else{
			System.out.println("Database was not deleted.");
		}
		scc.close();
		conn.close();
		stmt.close();
	}
	/*load from datafile
	 * User enters the path of the folder that contains the data files
	 * System reads the file and inserts into the appropriate records
	 * Search for different files the add each unique file format to the corresponding tables
	 */

	//*********************
	//Assume all input data files are correct in format and content
	public static void loadBookData(String pathName) throws NumberFormatException, SQLException{
		pathName = pathName + "\\book.txt";
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		String thisLine;
		String[] fields = new String[5];
		int i;
		try {
			BufferedReader br = new BufferedReader(new FileReader(pathName));
			while((thisLine = br.readLine()) != null){
				i=0;
				for(String fieldVal: thisLine.split("\t")){
					//fieldVal = {callNum(string), number of copies (int), title(string), author(s)(String), DOP(String)}
					System.out.println(fieldVal);
					fields[i] = fieldVal;
					//each iteration of this for loop is a new field
				}
				//*Be very careful of the exact syntax used, it may be dependant of SQL version
				stmt.executeUpdate("INSERT INTO Books (Call_Number, Number_of_Copies, Title, Author, Date_of_Publication) VALUES "
						+ "('"+fields[0]+"',"+Integer.parseInt(fields[1])+",'"+fields[2]+"','"+fields[3]+"','"+fields[4]+"');");
				//each iteration of the while loop is a new entry
			}
			br.close();
		} catch (IOException e){
			System.err.println("There was an error when opening book.txt");
			System.err.println("Error: " + e);
		}
		conn.close();
		stmt.close();
	}


	public static void loadCategoryData(String pathName) throws NumberFormatException, SQLException{
		pathName = pathName + "\\category.txt";
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();

		String thisLine;
		String[] fields = new String[3];
		int i;
		try {
			BufferedReader br = new BufferedReader(new FileReader(pathName));
			while((thisLine = br.readLine()) != null){
				i=0;
				for(String fieldVal: thisLine.split("\t")){
					//fieldVal = {Category ID (int), Max books(int), Loan period (int)}
					System.out.println(fieldVal);
					fields[i] = fieldVal;
					//each iteration of this for loop is a new field
				}
				stmt.executeUpdate("INSERT INTO Categories(Category_ID, Max_Books, Loan_Period) VALUES"
						+ "("+Integer.parseInt(fields[0])+","+Integer.parseInt(fields[1])+","+Integer.parseInt(fields[2])+");");
				//each iteration of the while loop is a new entry
			}
			br.close();
		} catch (IOException e){
			System.err.println("There was an error when opening category.txt");
			System.err.println("Error: " + e);
		}
		conn.close();
		stmt.close();
	}


	public static void loadCheckOutData(String pathName) throws NumberFormatException, SQLException{
		pathName = pathName + "\\check_out.txt";
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();

		String thisLine;
		String[] fields = new String[5];
		int i;
		try {
			BufferedReader br = new BufferedReader(new FileReader(pathName));
			while((thisLine = br.readLine()) != null){
				i=0;
				for(String fieldVal: thisLine.split("\t")){
					//fieldVal = {Call number, Copy number (int), User ID, Check-out date (DD/MM/YYYY), return date (DD/MM/YYYY)}
					System.out.println(fieldVal);
					fields[i] = fieldVal;
					//each iteration of this for loop is a new field
				}
				//*Be careful with the exact syntax of each entry (It is base on the data type)
				stmt.executeUpdate("INSERT INTO Checked_Out_Records(User_ID, Call_Number, Copy_Number, Check_Out_Date, Return_Date) "
						+ "VALUES('"+fields[0]+"','"+Integer.parseInt(fields[1])+"',"+fields[2]+",'"+fields[3]+"','"+fields[4]+"');");
				//each iteration of the while loop is a new entry
			}
			br.close();
		} catch (IOException e){
			System.err.println("There was an error when opening check_out.txt");
			System.err.println("Error: " + e);
		}
		conn.close();
		stmt.close();
	}

	public static void loadUserData(String pathName) throws SQLException{
		pathName = pathName + "\\user.txt";
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		String thisLine;
		String[] fields = new String[4];
		int i;
		try {
			BufferedReader br = new BufferedReader(new FileReader(pathName));
			while((thisLine = br.readLine()) != null){
				i=0;
				for(String fieldVal: thisLine.split("\t")){
					//fieldVal = {User ID, Name, Address, Category ID}
					System.out.println(fieldVal);
					fields[i] = fieldVal;
					//each iteration of this for loop is a new field
				}
				stmt.executeUpdate("INSERT INTO Library_Users(User_ID, Name, Address, Category_ID) "
						+ "VALUES ('"+fields[0]+"','"+fields[1]+"','"+fields[2]+"',"+fields[3]+");");
				//each iteration of the while loop is a new entry
			}
			br.close();
		} catch (IOException e){
			System.err.println("There was an error when opening user.txt");
			System.err.println("Error: " + e);
		}
		stmt.close();
		conn.close();
	}
	public static void loadBookCopies() throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("SELECT Number_of_Copies, Call_Number FROM Books;");
		//create records for each copy of a book based of the number of copies of a book
		while(rs.next()){
			for(int i =1; i <=rs.getInt(0);i++){
				stmt.execute("INSERT INTO Book_Copy (Call_Number, Copy_Number, CheckedOut_Record) VALUES ('"+rs.getString(1)+"',"+i+",FALSE)");
			}
		}
		rs = stmt.executeQuery("SELECT Call_Number, Copy_Number FROM Checked_out_Records WHERE Return_Date IS NOT NULL");
		//update those records of books which are already checked out
		while(rs.next()){
			stmt.execute("UPDATE Copy_Number SET CheckedOut_Record = TRUE WHERE Call_Number = '"+rs.getString(0)+"', Copy_Number = "+rs.getInt(1)+";");
		}
		rs.close();
		conn.close();
		stmt.close();
	}
	public static void loadAuthorTable() throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("SELECT Title, Author FROM Books");
		String[] authorList;
		while(rs.next()){
			authorList = rs.getString(1).split(",");
			for(int i =0; i<authorList.length;i++){
				stmt.executeQuery("INSERT INTO Authors(Author_Name, Book_Title) VALUES('"+authorList[i]+"','"+rs.getString(0)+"')");
			}
		}
		rs.close();
		conn.close();
		stmt.close();
	}

	public static void loadDatafile(String pathName){
		try {
			loadBookData(pathName);
		} catch (NumberFormatException | SQLException e1) {
			System.err.println("Error in loading book data: " + e1);
		}

		try {
			loadCheckOutData(pathName);
		} catch (NumberFormatException | SQLException e) {
			System.err.println("Error in loading check-out data: " + e);
		}
		try {
			loadCategoryData(pathName);
		} catch (NumberFormatException | SQLException e) {
			System.err.println("Error in loading category data: " + e);
		}
		try {
			loadUserData(pathName);
		} catch (SQLException e) {
			System.err.println("Error in loading user data: " + e);
		}
		try{
			loadBookCopies();
		} catch (SQLException e){
			System.err.println("Error in creating book copy table: " + e);
		}
		try {
			loadAuthorTable();
		} catch (SQLException e) {
			System.err.println("Error in creating author table: " + e);
		}
	}

	/*show number of records in each table
	 * Options to show the number of values in a certain table or all of the tables
	 * Using count(*) syntax
	 */
	public static void showTableRecords() throws SQLException{
		Connection conn = DriverManager.getConnection(DB_ID,User_Name,Password);
		Statement stmt = conn.createStatement();
		ResultSet rs = null;
		try {
			rs = stmt.executeQuery("SELECT"
					+ "(SELECT COUNT(*) FROM Books) AS BookCount,"
					+ "(SELECT COUNT(*) FROM Checked_Out_Records) AS RecordCount,"
					+ "(SELECT COUNT(*) FROM Categories) AS CategoryCount, "
					+ "(SELECT COUNT(*) FROM Library_Users) AS UserCount,"
					+ "(SELECT COUNT(*) FROM Authors) AS AuthorTableCount,"
					+ "(SELECT COUNT(*) FROM Book_Copy) AS NumberOfActualBooks;");
			while(rs.next()){
				//Assuming the index of rs.getstring starts at 0
				System.out.println("Total number of unique books: " + rs.getString(0));
				System.out.println("Total number of records for checked out books: " + rs.getString(1));
				System.out.println("Total number of categories: " + rs.getString(2));
				System.out.println("Total number of library users: " + rs.getString(3));
				//I should have a more detailed name for this statement
				System.out.println("Total number of author to book connections: " + rs.getString(4));
				System.out.println("Total number of physical books: " + rs.getString(5));
			}
		} catch (SQLException e) {
			System.err.println("Error: " + e );
			e.printStackTrace();
		}
		conn.close();
		stmt.close();
		rs.close();
	}
}
