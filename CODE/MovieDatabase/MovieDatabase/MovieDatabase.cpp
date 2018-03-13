// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "DatabaseClass.h"
#include "Other.h"
#include "ProjectClass.h"
using namespace std;



int main()
{
	Database Database; Database.Setup(100);
	
	string Query;


	//Database.PrintResults(Database.Storage);
	cout << "What film are you looking for? ";
	cin >> Query;

	try
	{
		Database.Search("Tits", Query);
	}
	catch(const std::out_of_range& oor)
	{
		cout << "That is not a valid field to search" << endl;
	}


	getchar();
	getchar();


	 
	Database.~Database();
	return 0;
}

