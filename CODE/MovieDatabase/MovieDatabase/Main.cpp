#include "Database.h"
#include "Library.h"
#include "Film.h"
#include "Templates.cpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

//s#include "CastCrewClass.h"
using namespace std;



int main()
{
	
	string Choice;
	char Box = 178;
	cout << "\n\n" << endl;
	for (int i = 0; i <= 50; i++) { cout << Box; }
	cout <<"\n\n  Welcome to the TrekStar Pictures Movie Database\n" << endl;
	for (int i = 0; i <= 50; i++) { cout << Box; }

	cout << "\n\n Please press enter to load the Database." << endl;

	getchar();

	Database Database("DATABASEFINAL.txt", "CASTCREWFINAL.txt.","MATERIALSFINAL.txt", 200);



	cout << "\n\nPress Enter to continue." << endl; getchar();


	/*

	while (Choice != "QUIT")
	{
		cout << "What would you like to do?" << endl;
		cout << "\nView Film Database - 1\n\nSearch Film Database - 2\n\nView Film Details - 3";
		cout << "\n\nQuit - QUIT\n\nChoice : ";
		cin >> Choice;
		

		if (Choice == "1")
		{
			Database.PrintResults("ASC");
			cout << "\nSorted By : " << Database.CURRENT_SORT << endl;
			cout << "Order : " << Database.CURRENT_SORT_TYPE << endl;
		}
	}

	
	*/

	//Database.SearchActor("1","FILMS");


	//getchar();


	Database.PrintResults("ASC");

	//Database.Storage;
	//int a = 1;

	Database.Search("TITLE","Star",'<');
	
	getchar();
	 
	//Database.~Database();
	return 0;
}
