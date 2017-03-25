#include "Date.h"
#define DEBUGMODE 0// 0 = DEBUG MODE deactivated = no debug output printing the object construction, destruction and functions extra notifications 
using namespace std;

//Date Class definitions---------------------------------------------------------------------------------

int Date::NbDate = 0;

//Default constructor
Date::Date() {
	Day = 0;
	Month = 0;
	Year = 0;
	NbDate++;
	if (DEBUGMODE)cout << "Date constructor done : " << Day << "/" << Month << "/" << Year << endl;
}

//Constructor with members inputs
Date::Date(int day0, int month0, int year0) {
	Day = day0;
	Month = month0;
	Year = year0;
	NbDate++;
	if (DEBUGMODE)cout << "Date constructor done : " << Day << "/" << Month << "/" << Year << endl;
}

//Destructor
Date::~Date() {
	NbDate--;
	if (DEBUGMODE)cout << "Destructor Date done" << endl;
}

//Copy constructor
Date::Date(const Date &date0) {
	Day = date0.Day;
	Month = date0.Month;
	Year = date0.Year;
	NbDate++;
	if (DEBUGMODE)cout << "Date copy constructor done : " << Day << "/" << Month << "/" << Year << endl;
}

//Get private a member
int Date::getNbObj() { return NbDate; }
//Get private a member
int Date::getDay() { return Day; }
//Get private a member
int Date::getMonth() { return Month; }
//Get private a member
int Date::getYear() { return Year; }

//Friend function for the output
ostream &operator<<(ostream &out, const Date &dateout) {
	out << dateout.Day << "/" << dateout.Month << "/" << dateout.Year << endl;
	return out;
}

