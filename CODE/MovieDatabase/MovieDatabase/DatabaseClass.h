#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "ProjectClass.h"
#include "Other.h"
using namespace std;



class Database
{
public:
	vector<Project> Storage; //Contains all films from database

	vector<Project> Temp; //A temp vector for search results

	~Database()
	{
		ofstream File;
		File.open("Testing.txt");
		//File << Storage[0].ID +"|"+ Storage[0].Genres + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" + Storage[0].ID + "|" +
		File.close();


	}


	void Setup()
	{
		const int MAX = 100; //Number of items to be loaded from Database
		string Line;
		ifstream FromFile("Database.txt");
		if (FromFile.is_open()) cout << "File sucessfully Loaded!" << endl; getchar();

		int i = 0;

		while (getline(FromFile, Line))
		{
			Project Film(Line);
			Film.Setup();
			Storage.push_back(Film);

			if (i == MAX) break;
			i++;
		}
	}

	void PrintResults(vector<Project> Input)//Prints out details of a number of films
	{
		cout << "\n\tTitle \t\t\tGenres \t\tRelease Date \t\tRuntime \t\tStatus" << endl;
		for (vector<Project>::const_iterator i = Input.begin(); i != Input.end(); i++)
		{
			Project Temp = *i;
			Temp.Details();
		}
	}

	void Search()
	{

		Temp.clear();
		string Query;
		cout << "What film are you looking for? ";
		cin >> Query;

		for (vector<Project>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
		{

			Project Result = *i;
			if ((ToLower(Result.Title)).find(ToLower(Query)) != string::npos)
			{
				Temp.push_back(Result);
			}
		}
		cout << "Here are the search results for: " << Query << endl;
		PrintResults(Temp);
	}
};