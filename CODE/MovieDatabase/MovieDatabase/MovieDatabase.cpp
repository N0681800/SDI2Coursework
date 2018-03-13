// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include "DatabaseClass.h"
#include "Other.h"
#include "ProjectClass.h"


using namespace std;

/*LOGIN STUFF
string Username, Password;
cout << "User name: ";
cin >> Username;
cout << "Password: ";
cin >> Password;
*/


int main()
{

	Database Database;
	Database.Setup();
	cout << Database.Storage.size() << " Films Loaded.";


	//Database.PrintResults(Database.Storage);
	Database.Search();
	cin;
	getchar();
	getchar();


	 
	Database.~Database();
	return 0;
}

