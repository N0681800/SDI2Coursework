#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "ProjectClass.h"
#include "Library.h"
#include "CastCrewClass.h"
using namespace std;


class Database
{
public:
	vector<Project> Storage; //Contains all films from database

	Database(string filmPath,string ccPath, int Max);

	~Database();

	void PrintResults(vector<Project> Input);//Prints out details of a number of films

	vector<Project> Search(string SearchField, string Query);//Searchs field for a value

	bool SaveData();//Saves the database

private:
	string filmPath; //Path to database

	string ccPath; //Path to cast crew database

	void Setup(int MAX);//Setups Database,input of #of films to be loaded

	vector<Project> Temp; //A temp vector for search results

	string GenerateID();//Generates a unique ID when creating a new project
};



Database::Database(string filmPath_,string ccPath_,int Max)
{
	filmPath = filmPath_;
	ccPath = ccPath_;
	Setup(Max);
}

Database::~Database()
{
	SaveData();
}

void Database::Setup(int MAX)
{
	string Line;
	ifstream FromFile(filmPath);
	if (FromFile.is_open()) cout << "File sucessfully Loaded!\n" << endl; getchar();

	while (getline(FromFile, Line))
	{
		Project Film(Line); Film.Setup();
		
		Storage.push_back(Film);
		
		if (Storage.size() == MAX) break;
	}

	cout << Storage.size() << " Films Loaded.\n"<<endl;
}

void Database::PrintResults(vector<Project> Input)//Prints out details of a number of films
{

	cout << setw(MaxTitleLength+3) << left << "Title" << Border;
	cout << setw(MaxGenreLength+6) << left << "Genres" << Border;
	cout  << setw(10) << left << "Released" << Border;
	cout  << setw(10) << left << "Runtime" << Border;
	cout  << setw(12) << left << "Status" <<Border<< endl;

	PrintTable();

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

bool Database::SaveData()
{
	bool Saved = false;
	ofstream File;
	File.open("Database.txt");
	for (vector<Project>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Project Temp = *i;
		File << Temp.ID + "|" + Temp.Title + "|" + VectorAsString(Temp.Genres) + "|" + Temp.Summary + "|" + VectorAsString(Temp.ProdComps) + "|" + VectorAsString(Temp.Locations) + "|" + Temp.ReleaseDate + "|" + Temp.Revenue + "|" + Temp.Runtime + "|" + VectorAsString(Temp.Languages) + "|" + Temp.Status << endl;;
	}
	Saved = true;
	File.close();
	return Saved;
}
