#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "DatabaseClass.h"
#include "Other.h"
using namespace std;


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

