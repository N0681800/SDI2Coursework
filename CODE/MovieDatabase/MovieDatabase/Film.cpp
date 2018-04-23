#include "Film.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>


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


	Status = 0;
	//if (rand() % 3 == 0) Status = 0;
	//else if (rand() % 3 == 1) Status = 1;
	//else Status = 2;


	//Set Material Info
	if (Status == 0)
	{
		if (GetDate(ReleaseDate) < "20040101")
		{
			//VHS
			string VHS = "0/VHS" + ID + "/" + Title + "/Mono/9.99/16:9/" + Languages[0];
			Material Temp(VHS);
			Materials.push_back(Temp);
		}	
	}


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

void Film::Save()
{

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

string Film::Material::FrameAspect::Disp()
{
	return w + ":" + h;
}

void Film::Material::FrameAspect::SetFA(string Input)
{
	string Data;
	stringstream LineOfData(Input);
	getline(LineOfData, Data, '/'); //getting data
	w = stoi(Data);
	getline(LineOfData, Data, '/');
	h = stoi(Data);
}

void Film::Material::Price::setPrice(string Input)
{
	string Data;
	stringstream LineOfData(Input);
	getline(LineOfData, Data, '.'); //getting data
	Dollars = stoi(Data);
	getline(LineOfData, Data, '.');
	Cent = stoi(Data);
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
	string TokenizedMaterial; int i = 0;
	vector<string> TempMaterialData;
	stringstream LineOfData(Info);
	while (getline(LineOfData, TokenizedMaterial, '/')) //getting data
	{
		TempMaterialData.push_back(TokenizedMaterial); //Store data in temp vector
	}
	Format = stoi(TempMaterialData[0]);
	ID = TempMaterialData[1];
	Title = TempMaterialData[2];
	AudioFormat = TempMaterialData[3];
	Cost = TempMaterialData[4];

	//Cost.setPrice(TempMaterialData[3]);

	FA = TempMaterialData[5];

	//FA.SetFA(TempMaterialData[4]);

	AudioLanguages = AddTokens(TempMaterialData[6]);

	if (Format != 0)
	{
		SubtitleLanguages = AddTokens(TempMaterialData[6]);
	}
	if (Format == 2)
	{
		SideOneInfo = TempMaterialData[7];
		SideTwoInfo = TempMaterialData[8];
	}

}

string Film::printMaterials()
{
	try
	{
		if (Materials.size() == 0)
		{
			throw 99;
		}
		for (vector<Material>::iterator i = Materials.begin(); i != Materials.end(); i++)
		{
			string MaterialList;
			MaterialList += i->getFormat();
			if (i != (Materials.end() - 1)) MaterialList += ',';

			return MaterialList;
		}
	}
	catch (int a)
	{
		return " ";
	}
}

/*
string Film::Material::SaveInfo()
{
	string Info = Format + "/" + ID + "/" + Title + "/" + AudioFormat + "/" + Cost.AsString() + "/" + FA.Disp() + "/" + VectorAsString(AudioLanguages);
	if (Format != 0) Info += "/" + VectorAsString(SubtitleLanguages);

	if (Format = 2)
	{
		Info += "/" + SideOneInfo + "/" + SideTwoInfo;
	}
	return Info;
}
*/