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

	Database Database("1.txt", "3.txt.","2.txt", 100);



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

	Database.SearchActorFilms(2);
	//Database.SearchActorName("Mark");

	Film* Pointer = (Find("12", &Database.Storage));

	if (Pointer) cout << Pointer->ID << endl;
	else
	{
		cout << "Null"<<endl;
	}


	//getchar();


	//Database.PrintResults("ASC");

	//Database.Storage;
	//int a = 1;

	//Database.Search("STATUS","100000",'<');
	
	getchar();
	 
	//Database.~Database();
	return 0;
}



template <class T>
int InsertInOrder(string ID, vector<T> *Vec)
{
	int start = 0, end = Vec->size() - 1;
	while (start <= end)
	{
		int M = floor(((end + start) / 2));

		if (Vec->at(M).ID < ID)
		{
			start = M + 1;
		}
		else
		{
			end = M - 1;
		}
	}
	return M;
}


/*
int main()
{
	srand(time(NULL));

	vector<int> Numbers;

	
	for (int i = 0;i < 10;i++)
	{
		int a = rand();
		vector<int>::iterator test = Numbers.begin();
		vector<int>::iterator index = (Numbers.begin() + InOrder(a, Numbers));
		Numbers.insert(index, a);

		for (vector<int>::iterator i = Numbers.begin(); i != Numbers.end(); i++)
		{
			cout << *i << ", ";
		}
		cout << "\n\n" << endl;

	//	if (Numbers.size() > 0) Numbers.insert(index, a);
		//else Numbers.push_back(a);

	}
	//Numbers.insert(InOrder(a, Numbers), a);
	



	for (vector<int>::iterator i = Numbers.begin(); i != Numbers.end(); i++)
	{
		cout << *i << endl;
	}

	getchar();
	return 0;
}
*/