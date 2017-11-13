package Project;

import java.util.Scanner;
import java.sql.*;


public class mainProgram {
	
	private static void menuOperations(){
		System.out.println("\n" + "-----Main menu-----");
		System.out.println("What kinds of operations would you like to perform?");
		System.out.println("1. Operations for administrator");
		System.out.println("2. Operations for library user");
		System.out.println("3. Operations for librarian");
		System.out.println("4. Operations for library director");
		System.out.println("5. Exit this program");
		System.out.print("Enter Your Choice: ");
		return;
	}

	public static void main(String[] args){
		//Avoid establishing one connection, instead connect for each query.
		System.out.println("Welcome to the library inquery system!");
		boolean menuLoop, adminLoop, userLoop, userIDLoop, libDirLoop, libLoop;
		Scanner sc = new Scanner(System.in);
		menuLoop = true;

		while(menuLoop){
			menuOperations();
			String choiceMain = sc.nextLine();

			switch(choiceMain){
			case "1":
				//Operations for administrator
				//potential log in function
				adminLoop = true;

				while(adminLoop){
					administrator.operations();
					String choiceAdmin = sc.nextLine();

					switch(choiceAdmin){
					case "1":
						//create all tables
						try {
							administrator.createTables();
						} catch (SQLException e1) {
							System.err.println("Error: "+e1);
							e1.printStackTrace();
						}
						break;

					case "2":
						//delete all tables
						System.out.println("\n" + "Are you certain you want to delete the tables?");
						System.out.println("Press \"Shift\" + \"y\" to delete, otherwise enter any key");
						String deleteKey = sc.nextLine();
						if(deleteKey.equals("Y")){
							try {
								administrator.deleteTables();
							} catch (SQLException e) {
								System.err.println("Error: "+e);
								//e.printStackTrace();
							}
						}
						else{
							System.out.println("Going back to administrator menu...");
						}
						break;

					case "3":
						//load from data file
						//need file reader and buffer reader
						System.out.println("\n" + "Type in the Souce Data Folder Path: ");
						String pathName = sc.nextLine();
						System.out.println("Processing...");
						//defined file reader and data entry methods in another class
						//This assumes the file has each .txt file required
						administrator.loadDatafile(pathName);

						System.out.println("Done! Data is inputed to the database!");
						break;

					case "4":
						System.out.println("Number of records in each table: ");
						try {
							administrator.showTableRecords();
						} catch (SQLException e) {
							System.err.println("Error: "+e);
							e.printStackTrace();
						}
						break;

					case "5": //return to the main menu
						System.out.println("Some message about leaving admin menu");
						adminLoop = false;
						break;

					default:
						System.out.println("Invalid option, please choose from the list of available options. ");
						break;
					}
				}
				break;

			case "2": //Operations for library user, *log in function/ create new user function??
				userLoop = true;

				while(userLoop){
					libraryUser.operations();
					String choiceUser = sc.nextLine();

					switch (choiceUser){
					case "1": //search for books function
						libraryUser.searchOperations();
						String searchChoice = sc.nextLine();

						switch (searchChoice){
						case "1":
							System.out.println("Please enter the call number of the book you would like to search for: ");
							String callNum = sc.next();
							//search function by call number
							try {
								libraryUser.searchBooksCallNumber(callNum);
							} catch (SQLException e) {
								System.err.println("Unfortunately there was an error while processing your request.");
							}
							break;

						case "2":
							//search function by title
							System.out.println("Please enter title of the book you would like to search for: ");
							String title = sc.next();
							try {
								libraryUser.searchBooksTitle(title);
							} catch (SQLException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
							break;

						case "3":
							//search function by author
							System.out.println("Please enter the name of the author you would like to search for: ");
							String author = sc.next();
							try {
								libraryUser.searchBooksAuthor(author);
							} catch (SQLException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
							break;

						default:
							System.out.println("Invalid option, please choose from the list of available options. ");
							break;
						}
						break;

					case "2": //show record of a user
						userIDLoop = true;

						while(userIDLoop){
							System.out.println("Enter The User ID: ");
							String userID = sc.nextLine();
							//Perhaps another query to check if the userID is valid first
							//maybe just another function to send a query that returns only the userIDs
							//then just parse through that and compare to the UserID entered
							try {
								libraryUser.userRecord(userID);
							} catch (SQLException e) {
								System.err.println("System was not able to connect to the database.");
							}
						}
						break;

					case "3": //exit the library user menu
						System.out.println("Returning to main menu.");
						userLoop = false;
						break;

					default:
						System.out.println("Invalid option, please choose from the list of available options. ");
						break;
					}
				}
				break;

			case "3": //Operations for librarian
				libLoop = true;
				String userID;
				int callNumber, copyNumber;

				while(libLoop){
					librarian.operations();
					String libChoice = sc.nextLine();

					switch(libChoice){
					case "1": //book borrowing function
						System.out.print("Enter The User ID: ");
						userID = sc.next();
						System.out.print("Enter The Call Number: ");
						callNumber = sc.nextInt();
						System.out.print("Enter The Copy Number: ");
						copyNumber = sc.nextInt();
						
						try {
							librarian.borrowBook(userID, callNumber, copyNumber);
						} catch (SQLException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						//book borrow function, takes in the above parameters
						//must consider invalid inputs, if the book is already out,
						//and must update the records about the new check out,
						//the number of books, and information related to the user.
						//returns a message to inform the librarian
						break;

					case "2": //book returning function
						System.out.print("Enter The User ID: ");
						userID = sc.next();
						System.out.print("Enter The Call Number: ");
						callNumber = sc.nextInt();
						System.out.print("Enter The Copy Number: ");
						copyNumber = sc.nextInt();
						
						try {
							librarian.returnBook(userID, callNumber, copyNumber);
						} catch (SQLException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						//return function, takes in the above as input
						//check if this is a valid return for the user,
						//update return date, check-out record of user, books available
						//returns a message to inform the librarian.
						//** can include if the book is overdue but not necessary.
						break;

					case "3": //returning to main menu
						System.out.println("Returning to main menu.");
						break;

					default:
						System.out.println("Invalid option, please choose from the list of available options. ");
						break;
					}
				}
				break;

			case "4":
				//Operations for library director
				libDirLoop = true;

				while(libDirLoop){
					librarianDir.operations();
					String libDirChoice = sc.next();

					switch(libDirChoice){
					case "1": //function to list un-returned book copies for a certain period.
						System.out.println("Type in the starting date [dd/mm/yyyy]: ");
						String startDate = sc.next();
						System.out.println("Type in the ending date [dd/mm/yyyy]: ");
						String endDate = sc.next();
						try {
							librarianDir.checkedOutBooks(startDate, endDate);
						} catch (SQLException e) {
							System.err.println("A matching borrow record is not found.");
						}
						break;

					case "2":
						libDirLoop = false;
						System.out.println("Returning to main menu.");
						break;

					default:
						System.out.println("Invalid option, please choose from the list of available options. ");
						break;
					}
				}
				break;

			case "5": //Exit this program
				System.out.println("Exiting library inquery system. ");
				menuLoop = false;
				break;

			default:
				System.out.println("Invalid option, please choose from the list of available options. ");
				break;
			}
		}
		sc.close();
	}
}
