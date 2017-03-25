#include "AppHeader.h"

/*
Project Assignment Bastien Gouila 23/03/2017
Write a program that keeps record of books that are in the library. The program stores following information about each book:
	- Name of the book
	- Id number of the book
	- Name of the person who borrowed this book
	- Date when the book is to be returned

The program uses an array of records to hold the books in the library and keeps track of who borrowed books and when they are due to be returned.
The program must have (at least) following commands:
	1. Initialize (clear all records)
	2. Save library records to disk
	3. Read library records from disk
	4. Add a new book to library
	5. Borrow a book
	6. Return a book
	7. Print a report which lists all books. First the ones that are out on a loan and then the ones that are available in the library.

Keeping a separate record of books and library card holders is considered an additional credit.
*/

using namespace std;



// Main function
int main() {
	cout << "Welcome to the Library Record Application !\n\nHere are the commands that you have access to:\n";
	Help();
	bool bDEBUG = false;
	do{
		string strCommand;
		LibraryRecord LibraryRec;
		do {
			getline(cin, strCommand);
			//Add a new book to the record------------------------------------------------------------------------
			if (strCommand == "NEW BOOK") {
				string strname;
				cout << "Enter the name of the new book" << endl;
				getline(cin, strname);
				int iID = LibraryRec.getLibraryBooks().size() + 1;
				LibraryRec.addBook(Book(strname, iID));
				cout << "Book added to the Record" << endl;
			}
			//Borrow or return a book or renew a borrowing of the record--------------------------------------------------------
			else if (strCommand == "RENEW" || strCommand == "BORROW"|| strCommand == "RETURN") {

				//Finding the book ID
				int iID = 0;
				cout << "Enter the book ID that you want to borrow, renew or return" << endl;
				do { 
					iID = enter_number();
					cin.get();//clear the cin buffer because we use also getline function
					if (iID > 0 && iID <= LibraryRec.getLibraryBooks().size()) { break; }
					else { 
						cout << "This book ID doesn't exist in that record" << endl;
						cout << "Here are the available books :" << endl;
						cout << LibraryRec;
					}
				} while (1);

				//Entering the date of the action
				cout << "Enter the DATE of your action:" << endl;

				cout << "Day : " << endl;
				int day = 0;
				do {
					day = enter_number();
					cin.get();//clear the cin buffer because we use also getline function
					if (day >= 1 && day <= 30) { break; }
					else {cout << "Please enter a day between 1 and 30" << endl;}
				} while (1);

				cout << "Month : " << endl;
				int month = 0;
				do {
					month = enter_number();
					cin.get();//clear the cin buffer because we use also getline function
					if (month >= 1 && month <= 12) { break; }
					else { cout << "Please enter a month between 1 and 12" << endl; }
				} while (1);

				cout << "Year : " << endl;
				int year = enter_number();
				cin.get();//clear the cin buffer because we use also getline function

				//Borrow the book
				if(strCommand == "BORROW"){
					//Entering the borrower name
					string strName;
					cout << "Enter your name :" << endl;
					getline(cin, strName);
					LibraryRec.borrowBook(iID - 1, strName, Date(day, month, year));
				}
				//Renew the borrowing
				else if (strCommand == "RENEW") {
					LibraryRec.renewBook(iID-1, Date(day, month, year));
				}
				//Return a book
				else {
					LibraryRec.returnBook(iID - 1, Date(day, month, year));
				}
			}
			//Save the record to an xml file---------------------------------------------------------------
			else if (strCommand == "SAVE") {
				bool bSave = LibraryRec.SaveLibRecords("LibraryRecord.xml");
			}
			//Replace the record from one an xml file----------------------------------------------------------
			else if (strCommand == "LOAD") {
				LibraryRec.RecoverLibRecords("LibraryRecord.xml");
				cout << LibraryRec;
			}
			//List the books in the records----------------------------------------------------------------
			else if (strCommand == "LIST") {
				cout << LibraryRec;
			}
			//List the books in the records----------------------------------------------------------------
			else if (strCommand == "CLEAR") {
				cout << "All books are going to be cleared from the record. Are you sure ? <Y/N>" << endl;
				getline(cin, strCommand);
				if(strCommand=="Y")LibraryRec.Clear();
			}
			//Display the available commands---------------------------------------------------------------
			else if (strCommand == "HELP") {
				Help();
			}
			//Stop the program-----------------------------------------------------------------------------
			else if (strCommand == "STOP") {
				break;//Go out of the loop
			}
			//Stop the program and display the possible memory leaks---------------------------------------
			else if (strCommand == "DEBUG") {
				bDEBUG = true;
				break;//Go out of the loop
			}
			//No valid command has been found--------------------------------------------------------------
			else {
				cout << "Command not found. Try HELP for displaying the commands available" << endl;
			}

		} while (1);
		break;
	}while(1);
	if (bDEBUG) { cout << "Memory leak detection(true or false) : " << _CrtDumpMemoryLeaks() << endl; }
	system("PAUSE");
return EXIT_SUCCESS;
}

