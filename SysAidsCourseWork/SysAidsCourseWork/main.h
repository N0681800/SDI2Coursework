#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Date
{
	int Day;
	int Month;
	int Year;
};

struct Film 
{ 
	int ID;
	string Title; 
	string Summary;
	Date ReleaseDate;
	string Location;
	string Language;
	int RunTime;
};

vector<Film> DataBase;