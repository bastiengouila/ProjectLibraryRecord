#include "AppHeader.h"
#define DEBUGMODE 0// 0 = DEBUG MODE deactivated = no debug output printing the object construction, destruction and functions extra notifications 
using namespace std;


//Main functions definitions-----------------------------------------------------------------------------
//Enter a number with cin and makes sure that a number has been entered
int enter_number(){
	int iValue;
	while (1)
	{

		cin >> iValue;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input " << endl;
		}
		else
			break;
		cout << "Try again" << endl;
	}
	return iValue;
}

//Display the available commands of the program
void Help() {
	cout << left << setw(10) << "-NEW BOOK";
	cout << "Register a new book" << endl;
	cout << left << setw(10) << "-RENEW";
	cout << "Renew your borrowing " << endl;
	cout << left << setw(10) << "-BORROW";
	cout << "Borrow a book" << endl;
	cout << left << setw(10) << "-RETURN";
	cout << "Return a book that you borrowed" << endl;
	cout << left << setw(10) << "-SAVE";
	cout << "Save the Library Record in an xml file" << endl;
	cout << left << setw(10) << "-LOAD";
	cout << "Load the Library Record from an xml file" << endl;
	cout << left << setw(10) << "-LIST";
	cout << "Display the book list by ID number" << endl;
	cout << left << setw(10) << "-CLEAR";
	cout << "Clear all book form the record" << endl;
	cout << left << setw(10) << "-STOP";
	cout << "Go out of the proram" << endl;
	cout << left << setw(10) << "-DEBUG";
	cout << "Stop the program and display if they are memory leaks" << endl;
	cout << left << setw(10) << "-HELP";
	cout << "Display the commands and their actions" << endl;
}