#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "DatabaseClass.h"
#include "Library.h"
#include "CastCrewClass.h"
#include <iomanip>
using namespace std;

class Project
{
private:
	string Input; //Line of Data from database to be split up
public:
	//All relevant Film Info
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

	vector<string> Cast;

	vector<string> Crew;

	Project(string Input_);
	
	~Project();
	
	void Setup();//Loads in Data

	void Overview();//Prints out all info of a chosen film

	void Details();//Prints out basic data for database
};

Project::Project(string Input_)
{
	Input = Input_;
}

Project::~Project() 
{

}

void Project::Setup()
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
	if (TempData[7] == "0") { Revenue = "N/A"; } else Revenue = TempData[7];
	Runtime = TempData[8];
	Languages = AddTokens(TempData[9]);
	Status = TempData[10];
	cout << "Loaded film ID number:" << ID << endl;
}

void Project::Overview()//Prints out all info of a chosen film
{
	cout << "\n\n\n\t\t" << Title << "\n\n\t\tID:" << ID;
	cout << "\n\nStatus: " << Status << "\n\nReleased: " << ReleaseDate << "\n\nRuntime: " << Runtime <<" mins";
	cout << "\n\nLanguages avalible in:" << VectorAsString(Languages);
	cout << "\n\nSummary:\n" << Summary << "\n\nGENRES:" << VectorAsString(Genres);; 
	cout << "\n\nProduction Companies:"; VectorAsString(ProdComps);
	cout << "\n\nLocations:"; VectorAsString(Locations);
	cout << "\n\nRevenue:" << Revenue;

}

void Project::Details()
{
	
	cout << setw(MaxTitleLength+3) << left << SetLength(Title, MaxTitleLength)<< Border;
	cout << setw(MaxGenreLength+6) << left << SetLength(VectorAsString(Genres), MaxGenreLength) << Border;
	cout  << setw(10) << left << ReleaseDate << Border;
	cout << setw(5) << left  << Runtime << setw(5) << right << "mins" <<Border;
	cout << setw(12) << left  << Status<< Border << endl;

	PrintTable();
}
