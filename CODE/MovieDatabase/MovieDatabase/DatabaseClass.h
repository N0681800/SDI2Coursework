#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "ProjectClass.h"
#include "Library.h"
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

	void Setup(int MAX);//Setups Database,input of #of films to be loaded

	void PrintResults(vector<Project> Input);//Prints out details of a number of films

	vector<Project> Search(string SearchField, string Query);//Searchs field for a value

	string GenerateID();//Generates a unique ID when creating a new project
};

void Database::Setup(int MAX)
{
	string Line;
	ifstream FromFile("Database.txt");
	if (FromFile.is_open()) cout << "File sucessfully Loaded!" << endl; getchar();

	while (getline(FromFile, Line))
	{
		Project Film(Line); Film.Setup();
		
		Storage.push_back(Film);
		
		if (Storage.size() == MAX) break;
	}

	cout << Storage.size() << " Films Loaded.";
}

void Database::PrintResults(vector<Project> Input)//Prints out details of a number of films
{
	cout << "\n\tTitle \t\t\tGenres \t\tRelease Date \t\tRuntime \t\tStatus" << endl;
	for (vector<Project>::const_iterator i = Input.begin(); i != Input.end(); i++)
	{
		Project Temp = *i;
		Temp.Details();
	}
}

vector<Project> Database::Search(string SearchField,string Query)//Searchs field for a value
{
	map<string, string> SearchFields; 
	
	Temp.clear();
	
	for (vector<Project>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Project Result = *i;

		SearchFields["ID"] = (Result.ID); SearchFields["Title"] = (Result.Title); SearchFields["Status"] = Result.Status;
		SearchFields["Genres"] = VectorAsString(Result.Genres); SearchFields["ProdComps"] = VectorAsString(Result.ProdComps);
		SearchFields["Locations"] = VectorAsString(Result.Locations); SearchFields["Languages"] = VectorAsString(Result.Languages);
		
		SearchFields["Revenue"] = Result.Revenue; //Special case
		SearchFields["Date"] = Result.ReleaseDate; //Special case
		SearchFields["Runtime"] = Result.Runtime; //Special case
		 

		if ((ToLower((SearchFields.find(SearchField)->second))).find(ToLower(Query)) != string::npos)
		{
			Temp.push_back(Result);
		}
	}
	cout << "Here are the search results for: " << Query << "in"<<SearchField<<endl;
	PrintResults(Temp);

	return Temp;
}

string Database::GenerateID()
{
	string ID, Line, CurrentID;
	ifstream File; File.open("Database.txt");
	bool IDFound = false;
	int i = 2;
	while (!IDFound)
	{
		ID = to_string(i);
		while (ID.length() < 6) { ID = "0" + ID; }

		getline(File, Line); stringstream IDToken(Line); getline(IDToken, CurrentID, '|');

		if (CurrentID == ID) i++;

		else IDFound = true;
	}
	return ID;
}
