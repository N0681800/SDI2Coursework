#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//Structs
struct Date

{
	int Day;
	int Month;
	int Year;
	string Display;
};

//Functions
vector<string> AddTokens(string Line)
{
	vector<string> temp;
	string TokenizedData;
	stringstream LineOfData(Line);
	while (getline(LineOfData, TokenizedData, ',')) //getting data
	{
		try {
			if (TokenizedData.substr(1, 1) == ",") { continue; }
			else temp.push_back(TokenizedData);
		}
		catch (exception e) {}
	}
	return temp;
}

void PrintVector(vector<string> Vector)
{
	for (vector<string>::const_iterator i = Vector.begin(); i != Vector.end(); i++)
	{
		cout << *i;
		if (i != (Vector.end() - 1)) cout << ',';
	}
}

//Classes
class Project
{
private:
	string Input; //Line of Data from database to be split up
public:
	string ID;
	string Title;
	vector<string> Genres;
	string Summary;
	vector<string> ProdComps;
	vector<string> Locations;
	string ReleaseDate;
	string Revenue;
	string Runtime;
	vector<string> Languages;
	string Status;

	//Constructor
	Project(string Input_)
	{
		Input = Input_;
	};
	//Deconstructor
	~Project()
	{

	};
	//Loads in Data
	void Setup()
	{
		string TokenizedData, TempData[11]; int i = 0;
		stringstream LineOfData(Input);
		while (getline(LineOfData, TokenizedData, '|')) //getting data
		{
			//cout << TokenizedData<<endl;
			TempData[i] = TokenizedData; //Store data in temp array
			i++;
		}

		ID = TempData[0];
		Title = TempData[1];
		Genres = AddTokens(TempData[2]);
		Summary = TempData[3];
		ProdComps = AddTokens(TempData[4]);
		Locations = AddTokens(TempData[5]);
		ReleaseDate = TempData[6];
		Revenue = TempData[7];
		Runtime = TempData[8];
		Languages = AddTokens(TempData[9]);
		Status = TempData[10];
		cout << "Loaded film ID number:" << ID << endl;
	}
	//Prints out Data
	void Overview()//Prints out all info of a chosen film
	{
		cout << "ID:" << ID;
		cout << "\nTITLE:" << Title;
		cout << "\nGENRES:"; PrintVector(Genres);
		cout << "\nSummary:" << Summary;
		cout << "\nProduction Companies:"; PrintVector(ProdComps);
		cout << "\nLocations:"; PrintVector(Locations);
		cout << "\nReleased:" << ReleaseDate;
		cout << "\nRevenue:" << Revenue;
		cout << "\nRuntime:" << Runtime;
		cout << "\nLanuages:"; PrintVector(Languages);
		cout << "\nStatus:" << Status;
	}

	void Details()//Prints out basic data for database
	{
		cout << Title << "\t\t"; PrintVector(Genres); cout << "\t\t" << ReleaseDate << "\t" << Runtime << "\t" << Status << endl;


	}
};

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
			if ((Result.Title).find(Query) != string::npos)
			{
				Temp.push_back(Result);
			}
		}
		cout << "Here are the search results for: " << Query << endl;
		PrintResults(Temp);
	}
};

/*

//Variables
//vector<Film> DataBase;

//Functions
Date GetAsDate(string input)//Turns string from Database into DateFormat
{
	Date Temp;
	Temp.Year = stoi(input.substr(6, 4));
	Temp.Month = stoi(input.substr(3, 2));
	Temp.Day = stoi(input.substr(0, 2));
	Temp.Display = input;
	return Temp;
}

void LoadDatabase(ifstream *Stream)//Loads in all the data from the database
{
	
	string Line;
	while (getline(*Stream, Line))
	{
		stringstream LineOfData(Line);
		string TokenizedData;
		string TempData[7];
		Film Temp;
		int i = 0;
		while (getline(LineOfData, TokenizedData, '|')) //getting data
		{
			TempData[i] = TokenizedData; //Store data in temp array
			i++;
		}
		// Inserting Into Tempory struct
		Temp.ID = TempData[0];
		Temp.Title = TempData[1];
		Temp.Summary = TempData[2];
		Temp.ReleaseDate = GetAsDate(TempData[3]);
		Temp.Location = TempData[4];
		Temp.Language = TempData[5];
		Temp.RunTime = stoi(TempData[6]);


		DataBase.push_back(Temp); //Add struct to Database
	}
}

void DisplayDatabase()
{
	cout << "ID#\tName\t\tRelease Date\t\tRuntime" << endl;
	for (int i = 0; i < DataBase.size(); i++)
	{
		cout << DataBase[i].ID << "\t" << DataBase[i].Title << "\t" << DataBase[i].ReleaseDate.Display<< "\t\t" << DataBase[i].RunTime << "mins" << endl;

	}
}
*/

