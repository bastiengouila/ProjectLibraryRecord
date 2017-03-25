#include "LibraryRecord.h"
#define DEBUGMODE 0// 0 = DEBUG MODE deactivated = no debug output printing the object construction, destruction and functions extra notifications 
using namespace std;

//LibraryRecords functions definitions-----------------------------------------------------------------------------
//Default constructor
LibraryRecord::LibraryRecord() {
	NbLibRec++;
	if (DEBUGMODE)cout << "Constructor LibraryRecord done" << endl;
}

//Destructor
LibraryRecord::~LibraryRecord() {
	NbLibRec--;
	if (DEBUGMODE)cout << "Destructor LibraryRecord done" << endl;
}

int LibraryRecord::NbLibRec = 0;

//Get private a member
int LibraryRecord::getNbObj() { return NbLibRec; }

//Get private a member
vector<Book> LibraryRecord::getLibraryBooks() { return LibraryBooks; }

//Copy constructor
LibraryRecord::LibraryRecord(const LibraryRecord &LibraryRecord0) : LibraryBooks(LibraryRecord0.LibraryBooks) {
	NbLibRec++;
	if (DEBUGMODE)cout << "LibraryRecord copy constructor done : " << endl;
}

//Clear the Libraty record = delete all the book from the vector
void LibraryRecord::Clear() {
	LibraryBooks.clear();
	cout << "Books cleared form the record" << endl;
}

//Add a book to the record
void LibraryRecord::addBook(Book &BookToAdd) {
	LibraryBooks.push_back(BookToAdd);//push a book at the end of the book vector
}

//Borrow one book of the vector
void LibraryRecord::borrowBook(int iIndex, string const BorrowerName, Date &BorrowDate) {
	LibraryBooks[iIndex].Borrow(BorrowerName, BorrowDate);//Use the borrow function of the book object indicated by the index
}

//Renew the borrowing one book of the vector
void LibraryRecord::renewBook(int iIndex, Date &DateRenew) {
	LibraryBooks[iIndex].Renew(DateRenew);//Use the renew function of the book object indicated by the index
}

//Return one book of the vector
void LibraryRecord::returnBook(int iIndex, Date &ReturnDate) {
	LibraryBooks[iIndex].Return(ReturnDate);//Use the return function of the book object indicated by the index
}

//Friend function for the output
ostream &operator<<(ostream &out, const LibraryRecord &librecout) {
	for (int i = 0; i < librecout.LibraryBooks.size(); i++) {
		out << librecout.LibraryBooks[i] << endl;
	}
	return out;
}

//Find and return a string field in a xml file by using the xml tags
string LibraryRecord::find_field(string strXMLFile, const string strXMLTag) {
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

//Convert an xml file as a string
string LibraryRecord::ConvertFileToString(const string filename) {
	string file, line, location, temperature;
	ifstream inputFile(filename);
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			//cout << line << '\n';
			file.append(line);
			line.erase();
		}
		inputFile.close();
	}
	return file;
}

//Save the Library Record to a xml file
bool LibraryRecord::SaveLibRecords(const string strXMLFileName) {
	ofstream myfile;
	myfile.open(strXMLFileName);//Create or open the xml file
	if (myfile.is_open()) {
		myfile << "<LibraryRecord>";//Place the xml tag
		for (int i = 0; i < LibraryBooks.size(); i++) {
			LibraryBooks[i].SaveBook(myfile);//Save every book in teh record
		}
		myfile << "</LibraryRecord>";
		myfile.close();//Close the file
		cout << " Record saved to : " << strXMLFileName << endl;
		return true;
	}
	else {
		cout << strXMLFileName << " Failed to open the file" << endl;
		return false;
	}
}

//Recovering a Library Record from a xml file
void LibraryRecord::RecoverLibRecords(const string strXMLFileName) {
	LibraryBooks.clear();
	string page = ConvertFileToString(strXMLFileName);//Convert the file to a string
	if (find_field(page, "LibraryRecord") != "EMPTY") {//if the xml file contains a Library Record
		Book book;
		while (find_field(page, "Book") != "EMPTY") {//while a book is present in the record we gather the data and add it
			LibraryBooks.push_back(book.RecoverBook(page));
			page = page.substr(page.find("</Book>") + sizeof("</Book>") - 1);//substring the file to get ride of the book already added to the new record
		}
	}//if not the Record returned is an empty one
	cout << " Record loaded from : " << strXMLFileName << endl;
}

