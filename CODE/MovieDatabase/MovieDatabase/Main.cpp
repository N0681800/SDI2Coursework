// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "DatabaseClass.h"
#include "Library.h"
#include "ProjectClass.h"
using namespace std;

int main()
{
	Database Database; Database.Setup(100);
	
	string Query;

	
	//Database.PrintResults(Database.Storage);
	Database.PrintResults(Database.Storage);

	//Database.SaveData();
	
	getchar();
	getchar();


	 
	//Database.~Database();
	return 0;
}

