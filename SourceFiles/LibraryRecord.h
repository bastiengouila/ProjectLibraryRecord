#pragma once
#ifndef LIBRARY_RECORD_HEADER_H
#define LIBRARY_RECORD_HEADER_H
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
#include "Book.h"

using namespace std;

//LibraryRecord Object declaration
class LibraryRecord {
	//Friend functions
	friend istream &operator >> (istream &in, LibraryRecord &librecin);
	friend ostream &operator<<(ostream &out, const LibraryRecord &librecout);
	//public functions and members
public:
	LibraryRecord();
	LibraryRecord(const LibraryRecord &LibraryRecord0);
	~LibraryRecord();
	static int NbLibRec;
	int getNbObj();
	vector<Book> getLibraryBooks();
	void Clear();
	void borrowBook(int iIndex, string const BorrowerName, Date &BorrowDate);
	void renewBook(int iIndex, Date &DateRenew);
	void returnBook(int iIndex, Date &ReturnDate);
	void addBook(Book &BookToAdd);
	string find_field(string strXMLFile, const string strXMLTag);
	bool SaveLibRecords(const string strXMLFileName);
	void RecoverLibRecords(const string strXMLFileName);
	string ConvertFileToString(const string filename);
	//private functions and members
private:
	vector<Book> LibraryBooks;
};

#endif