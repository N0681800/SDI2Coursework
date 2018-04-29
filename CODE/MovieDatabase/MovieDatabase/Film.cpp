#include "Film.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Library.h"
#include "Templates.cpp"

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
	else Revenue = stoi(TempData[7]);
	Runtime = stoi(TempData[8]);
	if (TempData[9] == "") Languages.push_back("English"); //Remove in future
	else Languages = AddTokens(TempData[9], ',');

	Status = (rand() % 3);

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
	cout << "\n\nProduction Companies:" << VectorAsString(ProdComps);
	cout << "\n\nLocations:" << VectorAsString(Locations);
	cout << "\n\nWeekly box office revenue:" << Revenue;

}

void Film::Details() //Prints out film details in table format
{
	cout << setw(6) << left << ID << BORDER;
	cout << setw(MAX_TITLE_LENGTH) << left << SetLength(Title, MAX_TITLE_LENGTH) << BORDER;
	cout << setw(MAX_GENRE_LENGTH) << left << SetLength(VectorAsString(Genres), MAX_GENRE_LENGTH) << BORDER;
	cout << setw(10) << left << PrintDate(ReleaseDate) << BORDER;
	cout << setw(5) << left << Runtime << setw(5) << right << "mins" << BORDER;
	cout << setw(2) << left << "$ " << setw(12) << Revenue <<setw(4)<<"/wk"<< BORDER;
	cout << setw(12) << left << getStatus() << BORDER;
	cout << setw(MAX_MATERIAL_LENGTH) << left << SetLength(printMaterials(), MAX_MATERIAL_LENGTH) << BORDER << endl;

	PrintTable(FILM_TABLE);
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
	default:
		return NULL;
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
	default:
		return NULL;
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

string Film::printMaterials() //returns string of avalible material formats
{
	try
	{
		if (Materials.size() == 0)
		{
			throw 4;
		}
		string MaterialList;
		for (vector<Material>::iterator i = Materials.begin(); i != Materials.end(); i++)
		{
			MaterialList += i->getFormat();
			if (i != (Materials.end() - 1)) MaterialList += ',';
		}
		return MaterialList;
	}
	catch (int E)
	{
		cout << Exceptions.find(E)->second << endl;
		return " ";
	}
}

string Film::Save() //returns string to write to file
{
	return ID + "|" + Title + "|" + VectorAsString(Genres) + "|" + Summary + "|" + VectorAsString(ProdComps) + "|" + VectorAsString(Locations) + "|" + to_string(ReleaseDate) + "|" + to_string(Revenue) + "|" + to_string(Runtime) + "|" + VectorAsString(Languages) + "|" + to_string(Status);
}

string Film::SaveMaterials() //concatinates all material save strings
{
	string MaterialOut = ID;

	for (vector<Film::Material>::const_iterator j = Materials.begin(); j != Materials.end(); j++)
	{
		Material Temp = *j;
		MaterialOut += Temp.SaveInfo();
	}
	return MaterialOut;
}

string Film::Material::SaveInfo() //Returns string to save material
{
	string Info = ("|" + to_string(Format) + "/" + ID + "/" + Title + "/" + AudioFormat + "/" + Cost + "/" + FA + "/" + VectorAsString(AudioLanguages));

	if (Format != 0) Info += "/" + VectorAsString(SubtitleLanguages);

	if (Format == 2) Info += "/" + SideOneInfo + "/" + SideTwoInfo;

	return Info;
}

Film::CrewMember::CrewMember(vector<string> Details)
{
	ID = Details[1];
	Name = Details[3];
	Roles.push_back(Details[2]);
	try {
		if (Details[0].length() != 1)
		{
			throw(1);
		}
		else
		{
			Gender = stoi(Details[0]);
		}
	}
	catch(int E)
	{
		cout << Exceptions.find(E)->second;
		Gender = 0;
	}
}

int Film::AddCrew(string input)
{
	vector<string> FilmCrew = AddTokens(input, '/'); //vector of crew
	int No = 0;
	for (vector<string>::iterator i = FilmCrew.begin(); i != FilmCrew.end(); i++)
	{
		vector<string> CrewDetails = AddTokens(*i, ',');

		while (CrewDetails[1].length() < 7)
		{
			CrewDetails[1] = "0" + CrewDetails[1];
		}
		try
		{
			if (CrewDetails.size() != 4)
			{
				throw 4;
			}
			else {
				CrewMember* Pointer;
				if (!(Pointer = (Find(CrewDetails[1], &Crew))))
				{
					Crew.push_back(CrewMember(CrewDetails));
					No++;
				}
				else
				{
					Pointer->Roles.push_back(CrewDetails[2]);
				}
				cout << "Loaded crew :" + CrewDetails[1] << endl;
			}
		}
		catch (int E)
		{
			cout << Exceptions.find(E)->second << endl;
		}
	}
	return No;
}

string Film::CrewMember::Save() //returns string to save details
{
	string toSave;

	for (vector<string>::iterator i = (Roles.begin()); i != Roles.end(); i++)
	{
		toSave += to_string(Gender)  + "," +  ID + "," + Roles[0] + "," + Name;
		if (i != Roles.end() - 1)
		{
			toSave += "/";
		}
	}
	
	return toSave;
}

string Film::SaveCrew() //concatinates all crew save strings
{
	string CrewSave;
	for (vector<CrewMember>::iterator i = Crew.begin(); i != Crew.end(); i++)
	{
		CrewSave += i->Save();
		if (i != Crew.end() - 1)
		{
			CrewSave += "/";
		}
	}
	return CrewSave;
}

void Film::PrintCrewInfo() //prints crew info in table format
{
	cout << "\t\tCrew Info" << endl;
	PrintTableHeader(CREW_TABLE);
	for (vector<CrewMember>::iterator i = Crew.begin(); i != Crew.end(); i++)
	{
		cout << setw(MAX_NAME_LENGTH) << left << i->Name << BORDER;
		cout << setw(10) << left << GetGender(i->Gender) << BORDER;
		cout << setw(40) << left << SetLength(VectorAsString(i->Roles),40) << BORDER<<endl;
		PrintTable(CREW_TABLE);
	}
}

void Film::PrintMaterialInfo() //prints all material info for given film
{
	cout << "\t\tMATERIAL INFO" << endl;
	for (vector<Material>::iterator i = Materials.begin(); i != Materials.end(); i++)
	{
		for (int j = 0; j < 50; j++)
		{
			cout << EDGE;
		}
		cout << "\nFormat : " << setw(15) << left << i->getFormat() << "\tID : " << setw(10) << left << i->ID << endl;
		cout << "\nTitle : " << i->Title << endl;
		cout << "\nFrameAspect : " << i->FA << "\tPrice : $" << i->Cost << endl;
		cout << "\nAudioformats : " << i->AudioFormat << endl;
		cout << "\nAudio Languages : " << VectorAsString(i->AudioLanguages) << endl;
		if (i->Format != 0) cout << "\nSubtitle Languages : " << VectorAsString(i->SubtitleLanguages) << endl;

		if (i->Format == 2)
		{
			cout << "Side One Info : \t" << i->SideOneInfo << endl;
			cout << "Side Two Info : \t" << i->SideTwoInfo << endl;
		}
		for (int j = 0; j < 50; j++)
		{
			cout << EDGE;
		}
		cout << endl;
	}
}