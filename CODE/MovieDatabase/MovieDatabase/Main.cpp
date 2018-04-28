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

	string Hi = VectorAsString(GetVectorInputs());

	string Choice;
	cout << "\n\n" << endl;
	for (int i = 0; i <= 50; i++) { cout << BOX; }
	cout << "\n\n  Welcome to the TrekStar Pictures Movie Database\n" << endl;
	for (int i = 0; i <= 50; i++) { cout << BOX; }

	cout << "\n\n Please press enter to load the Database." << endl;

	getchar();

	Database DB("DATABASEFINAL.txt", "CASTCREWFINAL.txt.", "MATERIALFINAL.txt", 10);

	cout << "\n\nPress Enter to continue." << endl;
	getchar();

	cout << "\nMain Menu" << endl;
	while ((Choice = PrintMenu({ "View Film Database","View Actor Database","Admin Login","Quit" })) != "4")
	{
		if (Choice == "1")
		{
			cout << "Film Menu" << endl;
			while ((Choice = PrintMenu({ "View Database","Search Database","View Film Information","Add Film","Edit Film Info","Delete Film","Return" })) != "7")
			{
				if (Choice == "1")
				{
					DB.ViewDatabase();
				}
				else if (Choice == "2")
				{
					DB.SearchDatabase();
				}
				else if (Choice == "3")
				{
					DB.FilmInfo();
				}
				else if (Choice == "4")
				{
					DB.AddFilm();
				}
				else if (Choice == "5")
				{

				}
				else if (Choice == "6")
				{

				}
			}
		}
		else if (Choice == "2")
		{
			//ACtor menu
		}
		else if (Choice == "3")
		{
			DB.LogIn();
		}
	}

	return 0;
}
