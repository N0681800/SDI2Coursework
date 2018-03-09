// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "main.h"
using namespace std;


Date GetAsDate(string input)
{
	Date Temp;
	//string subyear = input.substr(1, 4);
	//cout << subyear;
	Temp.Year = stoi(input.substr(0, 4));
	Temp.Month = stoi(input.substr(3, 2));
	Temp.Day = stoi(input.substr(5, 2));
	return Temp;
	
}

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
		while (getline(StandardInfo, Line))
		{
			stringstream linestream(Line);
			string item;
			string TempData[7];
			int i = 0;
			while (getline(linestream, item, '|')) //getting data
			{
				TempData[i] = item;
				i++;
			}
			// putting into struct
			temp.ID = TempData[0];
			temp.Title = TempData[1];
			temp.Summary = TempData[2];
			temp.ReleaseDate = GetAsDate(TempData[3]);
			temp.Location = TempData[4];
			temp.Language = TempData[5];
			temp.RunTime = stoi(TempData[6]);
			DataBase.push_back(temp);
		}	

		for (int i = 0; i < DataBase.size(); i++)
		{
			cout << "\nFilm ID: " << DataBase[i].ID << "  Film Name:" << DataBase[i].Title << "Released: "<<DataBase[i].ReleaseDate.Day << " of "<<DataBase[i].ReleaseDate.Month<< DataBase[i].ReleaseDate.Year <<endl;
			cout << "\n\nSummary: " << DataBase[i].Summary << endl;
		}		
		getchar();
	}
	

	return 0;
}

