#pragma once
#ifndef DATE_HEADER_H
#define DATE_HEADER_H
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

using namespace std;

//Date Object declaration
class Date {
	//Friend functions
	friend istream &operator >> (istream &in, Date &datein);
	friend ostream &operator<<(ostream &out, const Date &dateout);
	//public functions and members
public:
	Date();
	Date(int day0, int month0, int year0);
	Date(const Date &date0);
	~Date();
	static int NbDate;
	int getNbObj();
	int getDay();
	int getMonth();
	int getYear();
	//private functions and members
private:
	int Day;
	int Month;
	int Year;
};

#endif