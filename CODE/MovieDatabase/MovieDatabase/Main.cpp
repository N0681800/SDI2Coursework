// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "DatabaseClass.h"
#include "Library.h"
#include "ProjectClass.h"
using namespace std;

int main()
{
	Database Database("CompleteDatabase.txt",200);
	
	getchar();

	Database.PrintResults(Database.Storage);
	//Database.SaveData();
	
	getchar();
	getchar();


	 
	//Database.~Database();
	return 0;
}

