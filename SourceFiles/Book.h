#pragma once
#ifndef BOOK_HEADER_H
#define BOOK_HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _ALLOW_MSC_VER_MISMATCH
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include <algorithm>    // std::set_intersection, std::sort
#include <vector>       // std::vector
#include <cmath>
#include <memory>
#include "Date.h"

using namespace std;

//Book Object declaration
class Book {
	//Friend functions
	friend istream &operator >> (istream &in, Book &bookin);
	friend ostream &operator<<(ostream &out, const Book &bookout);
	//public functions and members
public:
	Book();
	Book(string bookname0, int bookID0);
	Book(string bookname0, int bookID0, string bookborrower0, bool borrow0, bool breturn0, Date &dateborrow0, Date &datereturn0);
	Book(const Book &book0);
	~Book();
	static int NbBook;
	bool Borrow(string const BorrowerName, Date &BorrowDate);
	bool Return(Date &ReturnDate);
	bool Renew(Date &DateRenew);
	string find_field(string strXMLFile, const string strXMLTag);
	void SaveBook(ofstream &file);
	Book RecoverBook(const string strXMLFile);
	int getNbObj();
	string getBookName();
	int getBookID();
	string getBookBorrower();
	Date* getBorrowDate();
	Date* getReturnDate();
	bool getBorrowed();
	bool getReturned();
	//private functions and members
private:
	string BookName;
	int BookID;
	string BookBorrower;
	Date* BorrowDate;
	Date* ReturnDate;
	bool Borrowed;
	bool Returned;
};

#endif