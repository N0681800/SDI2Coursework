#include "Film.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Library.h"

Film::Film(string Input_)
{
	Input = Input_;
}

Film::~Film()
{

}

void Film::Setup()
{
	string TokenizedData, TempData[11]; int i = 0;
	stringstream LineOfData(Input);
	while (getline(LineOfData, TokenizedData, '|')) //getting data
	{
		//cout << TokenizedData<<endl;
		TempData[i] = TokenizedData; //Store data in temp array
		i++;
	}
	int a = rand();
	

	ID = TempData[0];
	Title = TempData[1];
	Genres = AddTokens(TempData[2]);
	Summary = TempData[3];
	ProdComps = AddTokens(TempData[4]);
	Locations = AddTokens(TempData[5]);
	ReleaseDate = GetDate(TempData[6]);
	if (TempData[7] == "0") { Revenue = 0; }
	else Revenue = stoi(TempData[7])/22;
	Runtime = stoi(TempData[8]);
	Languages = AddTokens(TempData[9]);

	if (rand() % 3 == 0) Status = 0;
	else if (rand() % 3 == 1) Status = 1;
	else Status = 2;

	cout << "Loaded film ID number:" << ID << endl;
}

void Film::Overview()//Prints out all info of a chosen film
{
	cout << "\n\n\n\t\t" << Title << "\n\n\t\tID:" << ID;
	cout << "\n\nStatus: " << getStatus() << "\n\nReleased: " << PrintDate(ReleaseDate) << "\n\nRuntime: " << Runtime << " mins";
	cout << "\n\nLanguages avalible in:" << VectorAsString(Languages);
	cout << "\n\nSummary:\n" << Summary << "\n\nGENRES:" << VectorAsString(Genres);;
	cout << "\n\nProduction Companies:"; VectorAsString(ProdComps);
	cout << "\n\nLocations:"; VectorAsString(Locations);
	cout << "\n\nRevenue:" << Revenue;

}

void Film::Details()
{
	const int MaxTitleLength = 35;
	const int MaxGenreLength = 20;
	char Border = 179;


	cout << setw(MaxTitleLength + 3) << left << SetLength(Title, MaxTitleLength) << Border;
	cout << setw(MaxGenreLength + 6) << left << SetLength(VectorAsString(Genres), MaxGenreLength) << Border;
	cout << setw(10) << left << PrintDate(ReleaseDate) << Border;
	cout << setw(5) << left << Runtime << setw(5) << right << "mins" << Border;
	cout << setw(2) << left << "$ " << setw(12) << Revenue <<setw(4)<<"/wk"<<  Border;
	cout << setw(12) << left << getStatus() << Border << endl;

	PrintTable();
}

string Film::getStatus()
{
	switch (Status)
	{
	case 0:
		return "Released";
	case 1:
		return "Now Playing";
	case 2:
		return "Unreleased";

	}
}