#include "Book.h"
#define DEBUGMODE 0// 0 = DEBUG MODE deactivated = no debug output printing the object construction, destruction and functions extra notifications 
using namespace std;


//Book funtions definitions-------------------------------------------------------------------------------
int Book::NbBook = 0;
//Default constructor
Book::Book() {
	BookID = 0;
	BookName = "\0";
	Borrowed = false;
	Returned = true;
	BorrowDate = new Date();
	ReturnDate = new Date();
	NbBook++;
	if (DEBUGMODE)cout << "Book constructor done : ID = " << BookID << " Name = " << BookName << endl;
}

//Constructor with partial member initialization = default book without borrow states
Book::Book(string bookname0, int bookID0) {
	BookID = bookID0;
	BookName = bookname0;
	Borrowed = false;
	Returned = true;
	BorrowDate = new Date();
	ReturnDate = new Date();
	NbBook++;
	if (DEBUGMODE)cout << "Book constructor done : ID = " << BookID << " Name = " << BookName << endl;
}

//Constructor with total member initialization
Book::Book(string bookname0, int bookID0, string bookborrower0, bool borrow0, bool breturn0, Date &dateborrow0, Date &datereturn0) {
	BookID = bookID0;
	BookName = bookname0;
	BookBorrower = bookborrower0;
	Borrowed = borrow0;
	Returned = breturn0;
	BorrowDate = new Date(dateborrow0);
	ReturnDate = new Date(datereturn0);
	NbBook++;
	if (DEBUGMODE)cout << "Book constructor done : ID = " << BookID << " Name = " << BookName << endl;
}

//Destructor
Book::~Book() {
	NbBook--;
	delete BorrowDate;
	delete ReturnDate;
	if (DEBUGMODE)cout << "Destructor Book done" << endl;
}

//Copy constructor
Book::Book(const Book &book0) {
	BookID = book0.BookID;
	BookName = book0.BookName;
	BookBorrower = book0.BookBorrower;
	Borrowed = book0.Borrowed;
	Returned = book0.Returned;
	BorrowDate = new Date(*book0.BorrowDate);
	ReturnDate = new Date(*book0.ReturnDate);
	NbBook++;
	if (DEBUGMODE)cout << "Book copy constructor done : " << "Book ID = " << BookID << " Book Name = " << BookName << endl;
}

bool Book::Borrow(const string BorrowerName, Date &DateBorrow) {
	if (Borrowed == false && Returned == true) {
		delete BorrowDate;//delete the dynamic object
		BorrowDate = new Date(DateBorrow);//recreate the dynamic object with the new value
		delete ReturnDate;//delete the dynamic object
		int Month = DateBorrow.getMonth() + 1;
		int Year = DateBorrow.getYear();
		if (Month > 12) { Month = 1; Year++; }
		ReturnDate = new Date(DateBorrow.getDay(), Month, Year);//recreate the dynamic object with the new value
		BookBorrower = BorrowerName;
		Returned = false;
		Borrowed = true;
		cout << "Book borrowed" << endl;
		cout << "Book needs to be returned for the : " << *ReturnDate << endl;
		return true;
	}
	else if (Borrowed == true && Returned == false) {
		cout << "Impossible = book already borrowed but not returned yet" << endl;
		return false;
	}
}

//Renew the borrowing of a book
bool Book::Renew(Date &DateRenew) {
	if (Borrowed == true && Returned == false) {//Check if the book has been borrowed
		double timeborrow = BorrowDate->getDay() + BorrowDate->getMonth() * 30 + BorrowDate->getYear() * 12 * 30;
		double timereturn = DateRenew.getDay() + DateRenew.getMonth() * 30 + DateRenew.getYear() * 12 * 30;
		if (timereturn >= timeborrow) {//Check if the renew date is equal or later than the borrow date
			delete BorrowDate;//delete the dynamic object
			BorrowDate = new Date(DateRenew);//recreate the dynamic object with the new value
			delete ReturnDate;//delete the dynamic object
			int Month = DateRenew.getMonth() + 1;
			int Year = DateRenew.getYear();
			if (Month > 12) { Month = 1; Year++; }
			ReturnDate = new Date(DateRenew.getDay(), Month, Year);//recreate the dynamic object with the new value
			Returned = false;
			Borrowed = true;
			cout << "Book due date renew" << endl;
			cout << "Book needs to be returned for the : " << *ReturnDate << endl;
			return true;
		}
		else {
			cout << "Impossible = renew date is before the borrow date" << endl;
			return false;
		}
	}
	else {
		cout << "Impossible = Book hasn't been borrowed yet" << endl;
		return false;
	}
}

//Return a book
bool Book::Return(Date &DateReturn) {
	if (Returned == false && Borrowed == true) {//Check if the book has been borrowed before
		double timeborrow = BorrowDate->getDay() + BorrowDate->getMonth() * 30 + BorrowDate->getYear() * 12 * 30;
		double timereturn = DateReturn.getDay() + DateReturn.getMonth() * 30 + DateReturn.getYear() * 12 * 30;
		if (timereturn >= timeborrow) {//Check if the return date is later than the borrow date
			Returned = true;
			Borrowed = false;
			cout << "Book returned" << endl;
			cout << "Returned the : " << DateReturn << endl;
			delete BorrowDate;//delete the dynamic object
			delete ReturnDate;//delete the dynamic object
			BorrowDate = new Date();//reset the date
			ReturnDate = new Date();//reset the date
			return true;
		}
		else {
			cout << "Impossible = return date is before the borrow date" << endl;
			return false;
		}
	}
	else if (Borrowed == false && Returned == true) {
		cout << "Impossible = book already returned" << endl;
		return false;
	}
}

//Get private a member
int Book::getNbObj() { return NbBook; }

//Get private a member
string Book::getBookName() { return BookName; }

//Get private a member
int Book::getBookID() { return BookID; }

//Get private a member
string Book::getBookBorrower() { return BookBorrower; }

//Get private a member
Date* Book::getBorrowDate() { return BorrowDate; }

//Get private a member
Date* Book::getReturnDate() { return ReturnDate; }

//Get private a member
bool Book::getBorrowed() { return Borrowed; }

//Get private a member
bool Book::getReturned() { return Returned; }

//Friend function for the output
ostream &operator<<(ostream &out, const Book &bookout) {
	out << "Book info : " << "ID = " << bookout.BookID << right << setw(20);
	out << "Name = " << bookout.BookName << endl;
	if (bookout.Borrowed) {
		out << "Borrower : " << right << setw(20) << bookout.BookBorrower << left << setw(20) << endl;
		out << "Borrow the : " << *bookout.BorrowDate << left << setw(20) << endl;
		out << "Due date : " << *bookout.ReturnDate << endl;
	}
	return out;
}

//Find and return a string field in a xml file by using the xml tags
string Book::find_field(string strXMLFile, const string strXMLTag) {
	/*Example:
	//size_t poslocation = page.find("<tag>");	position of <tag> in the string
	//size_t poslocationend = page.find("</tag>");position of </tag> in the string
	//poslocationend - poslocation = lenght of the string between the tags
	//We delete the tags parts by reducing the lenght of the sequence "<tag>" with (sizeof("<tag>") - 1)
	//strtag = page.substr(page.find("<tag>") + (sizeof("<tag>") - 1), page.find("</tag>") - page.find("<tag>") - (sizeof("<tag>") - 1));*/

	string strRet = "EMPTY";
	int itagfound = 0;

	//Non flexible way
	/*if (strXMLTag == "tag") {
	strRet = strXMLFile.substr(strXMLFile.find("<tag>") + (sizeof("<tag>") - 1), strXMLFile.find("</tag>") - strXMLFile.find("<tag>") - (sizeof("<tag>") - 1));
	}*/

	//Flexible way = works with all xml tags
	string strTagXML = "<" + strXMLTag + ">";
	string strTagXMLEnd = "</" + strXMLTag + ">";
	if ((strXMLFile.find(strTagXML) != string::npos) && (strXMLFile.find(strTagXMLEnd) != string::npos)) {
		strRet = strXMLFile.substr(strXMLFile.find(strTagXML) + strTagXML.size(), strXMLFile.find(strTagXMLEnd) - strXMLFile.find(strTagXML) - strTagXML.size());
	}
	else {
		if (DEBUGMODE) cout << strTagXML << " tag not found" << endl;
	}
	return strRet;
}

//Save the book to a xml file
void Book::SaveBook(ofstream &file) {
	//All the members of the object are placed between different xml tags
	file << "\n<Book>";//Place the xml tag
	file << "\n<BookID>";
	file << BookID;
	file << "</BookID>";
	file << "\n<BookName>";
	file << BookName;
	file << "</BookName>";
	file << "\n<BookBorrower>";
	file << BookBorrower;
	file << "</BookBorrower>";
	file << "\n<Borrowed>";
	file << Borrowed;
	file << "</Borrowed>";
	file << "\n<BorrowDate>";
	file << "\n<DayBorrow>";
	file << BorrowDate->getDay();
	file << "</DayBorrow>";
	file << "<MonthBorrow>";
	file << BorrowDate->getMonth();
	file << "</MonthBorrow>";
	file << "<YearBorrow>";
	file << BorrowDate->getYear();
	file << "</YearBorrow>";
	file << "</BorrowDate>";
	file << "\n<ReturnDate>";
	file << "\n<DayReturn>";
	file << ReturnDate->getDay();
	file << "</DayReturn>";
	file << "<MonthReturn>";
	file << ReturnDate->getMonth();
	file << "</MonthReturn>";
	file << "<YearReturn>";
	file << ReturnDate->getYear();
	file << "</YearReturn>";
	file << "</ReturnDate>";
	file << "\n<Returned>";
	file << Returned;
	file << "</Returned>";
	file << "</Book\n>";
}

//Recovering a Book from a xml previously converted file as a string
Book Book::RecoverBook(const string strXMLFile) {
	string bookname = find_field(strXMLFile, "BookName");
	int bookID = stoi(find_field(strXMLFile, "BookID"));
	string borrowname = find_field(strXMLFile, "BookBorrower");
	bool bborrow = stoi(find_field(strXMLFile, "Borrowed"));
	int dayborrow = stoi(find_field(strXMLFile, "DayBorrow"));
	int monthborrow = stoi(find_field(strXMLFile, "MonthBorrow"));
	int yearborrow = stoi(find_field(strXMLFile, "YearBorrow"));
	int dayreturn = stoi(find_field(strXMLFile, "DayReturn"));
	int monthreturn = stoi(find_field(strXMLFile, "MonthReturn"));
	int yearreturn = stoi(find_field(strXMLFile, "YearReturn"));
	bool breturn = stoi(find_field(strXMLFile, "Returned"));
	return Book(bookname, bookID, borrowname, bborrow, breturn, Date(dayborrow, monthborrow, yearborrow), Date(dayreturn, monthreturn, yearreturn));
}

