#include "Database.h"
#include "Library.h"
#include "Film.h"
#include "Templates.cpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{

	string Choice;
	cout << "\n\n" << endl;
	for (int i = 0; i <= 50; i++) { cout << BOX; }
	cout << "\n\n  Welcome to the TrekStar Pictures Movie Database\n" << endl;
	for (int i = 0; i <= 50; i++) { cout << BOX; }

	cout << "\n\n Please press enter to load the Database." << endl;

	getchar();

	Database DB("DATABASEFINAL.txt", "CASTCREWFINAL.txt.", "MATERIALFINAL.txt", 50);

	cout << "\n\nPress Enter to continue." << endl;
	getchar();
	

	cout << "\nMain Menu" << endl;
	while ((Choice = PrintMenu({ "View Film Database","View Actor Database","Admin Login","Quit" })) != "4")
	{
		if (Choice == "1")
		{
			
			PrintDivider(); cout << "Film Menu" << endl;
			while ((Choice = PrintMenu({ "View Database","Search Database","View Film Information","Add Film","Edit Film Info","Delete Film","Return" })) != "7")
			{
				if (Choice == "1")
				{
					PrintDivider();
					DB.ViewDatabase();
				}
				else if (Choice == "2")
				{
					PrintDivider();
					DB.SearchDatabase();
				}
				else if (Choice == "3")
				{
					PrintDivider();
					DB.FilmInfo();
				}
				else if (Choice == "4")
				{
					PrintDivider();
					DB.AddFilm();
				}
				else if (Choice == "5")
				{
					PrintDivider();
					DB.EditFilm();
				}
				else if (Choice == "6")
				{
					PrintDivider();
					DB.DeleteFilm();
				}
			}
		}
		else if (Choice == "2")
		{
			PrintDivider();  cout << "Actor Menu" << endl;
			while ((Choice = PrintMenu({ "View Actor Database", "Search Actor Database","View Actor Overview","Return" })) != "4")
			{
				if (Choice == "1")
				{
					PrintDivider();
					DB.ViewActorDatabase();
				}
				else if (Choice == "2")
				{
					PrintDivider();
					DB.SearchActorDatabase();
				}
				else if (Choice == "3")
				{
					PrintDivider();
					DB.ActorOverview();
				}
			}
		}
		else if (Choice == "3")
		{
			PrintDivider();
			DB.LogIn();
		}
	}

	return 0;
}
