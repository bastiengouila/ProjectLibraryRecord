#pragma once
#ifndef APPHEADER_H
#define APPHEADER_H
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
#include "LibraryRecord.h"

using namespace std;

//Main functions declaration
void Help();
int enter_number();
#endif