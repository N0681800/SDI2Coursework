#include "Film.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Library.h"

Film::Film(string Input)
{
	vector<string> TempData = AddTokens(Input, '|');

	ID = TempData[0];
	Title = TempData[1];
	Genres = AddTokens(TempData[2], ',');
	Summary = TempData[3];
	ProdComps = AddTokens(TempData[4], ',');
	Locations = AddTokens(TempData[5], ',');
	ReleaseDate = stoi(TempData[6]);
	if (TempData[7] == "0") { Revenue = 0; }
	else Revenue = stoi(TempData[7]) / 22;
	Runtime = stoi(TempData[8]);
	if (TempData[9] == "") Languages.push_back("English"); //Remove in future
	else Languages = AddTokens(TempData[9], ',');

	Status = 0;

	cout << "Loaded: " << ID << endl;
}

Film::~Film()
{

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
	const int MaxMaterialLength = 15;
	char Border = 179;

	cout << setw(6) << left << ID << Border;
	cout << setw(MaxTitleLength + 3) << left << SetLength(Title, MaxTitleLength) << Border;
	cout << setw(MaxGenreLength + 6) << left << SetLength(VectorAsString(Genres), MaxGenreLength) << Border;
	cout << setw(10) << left << PrintDate(ReleaseDate) << Border;
	cout << setw(5) << left << Runtime << setw(5) << right << "mins" << Border;
	cout << setw(2) << left << "$ " << setw(12) << Revenue <<setw(4)<<"/wk"<<  Border;
	cout << setw(12) << left << getStatus() << Border;
	cout << setw(18) << left << SetLength(printMaterials(),MaxMaterialLength) << Border << endl;

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


string Film::Material::getFormat()
{
	switch (Format)
	{
	case 0:
		return "VHS";
	case 1:
		return "DvD";
	case 2:
		return "DSDvD";
	case 3:
		return "ComboBoxSet";
	case 4:
		return "Blu-ray";
	}
}


Film::Material::Material(string Info)
{
	vector<string> TempMaterialData = AddTokens(Info, '/');

	Format = stoi(TempMaterialData[0]);

	ID = TempMaterialData[1];

	Title = TempMaterialData[2];

	AudioFormat = TempMaterialData[3];

	Cost = TempMaterialData[4];

	FA = TempMaterialData[5];

	AudioLanguages = AddTokens(TempMaterialData[6],',');

	if (Format != 0)
	{
		SubtitleLanguages = AddTokens(TempMaterialData[6],',');
	}
	if (Format == 2)
	{
		SideOneInfo = TempMaterialData[7];
		SideTwoInfo = TempMaterialData[8];
	}

	cout << "Loaded :" + ID << endl;

}

string Film::printMaterials()
{
	try
	{
		if (Materials.size() == 0)
		{
			throw 99;
		}
		string MaterialList;
		for (vector<Material>::iterator i = Materials.begin(); i != Materials.end(); i++)
		{
			MaterialList += i->getFormat();
			if (i != (Materials.end() - 1)) MaterialList += ',';
		}
		return MaterialList;
	}
	catch (int a)
	{
		return " ";
	}
}

string Film::Save()
{
	return ID + "|" + Title + "|" + VectorAsString(Genres) + "|" + Summary + "|" + VectorAsString(ProdComps) + "|" + VectorAsString(Locations) + "|" + to_string(ReleaseDate) + "|" + to_string(Revenue) + "|" + to_string(Runtime) + "|" + VectorAsString(Languages) + "|" + to_string(Status);
}

string Film::SaveMaterials()
{
	string MaterialOut = ID;

	for (vector<Film::Material>::const_iterator j = Materials.begin(); j != Materials.end(); j++)
	{
		Material Temp = *j;
		MaterialOut += Temp.SaveInfo();

	}
	return MaterialOut;
}

string Film::Material::SaveInfo()
{
	string Info = ("|" + to_string(Format) + "/" + ID + "/" + Title + "/" + AudioFormat + "/" + Cost + "/" + FA + "/" + VectorAsString(AudioLanguages));

	if (Format != 0) Info += "/" + VectorAsString(SubtitleLanguages);

	if (Format == 2) Info += "/" + SideOneInfo + "/" + SideTwoInfo;

	return Info;
}
