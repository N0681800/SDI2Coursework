// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "main.h"
using namespace std;


int main()
{
	
	string Username, Password;
	bool FileReady = false;
	string Line;
	Film temp;

	ifstream StandardInfo("standardinfo.txt");	
	FileReady = StandardInfo.is_open();//file setup

	if (!FileReady) cout << "database can't be loaded pelase try again later";
	cout << "User name: ";
	cin >> Username;
	cout << "Password: ";
	cin >> Password;
	while (FileReady) //main program loop
	{


		while (getline(StandardInfo, Line)) {
			cout << Line;
			temp.ID = ;
			temp.Title = ;
			temp.Summary = ;
			temp.ReleaseDate = ;
			temp.Location = ; 
			temp.Language= ;
			temp.RunTime = ;
		}


	}
	getchar();

	return 0;
}

