#pragma once
#include "Library.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include "ActorClass.h"

using namespace std;

Actor::Actor(string FilmID,vector<string> Info)
{
	ID = Info[2];
	Gender = stoi(Info[1]);
	Name = Info[3];
	AddFilm(FilmID, Info[0]);

	cout << "Loaded Actor: " + ID <<endl;
}

void Actor::Details() {
	cout << setw(7) << left << ID << BORDER;
	cout << setw(MAX_NAME_LENGTH) << left << Name << BORDER;
	cout << setw(10) << left << GetGender(Gender) << BORDER;
}

void Actor::DeleteFilm(string filmID)
{
	for (map<string, vector<string>>::iterator i = FilmRole.begin(); i != FilmRole.end(); i++)
	{
		if (i->first == filmID)
		{
			FilmRole.erase(i);
			if (FilmRole.size() == 0)
			{
				delete this;
			}
		}	
	}
}

string Actor::GetRole(string filmID)
{
	return VectorAsString(FilmRole[filmID]);
}

string Actor::Save(string filmID)
{
	return GetRole(filmID) + "," + to_string(Gender) + "," + ID + "," + Name;
}

void Actor::AddFilm(string FilmID,string Character) {
	FilmRole[FilmID].push_back(Character);
}

vector<string> Actor::ReturnFilmIDs()
{
	vector<string> Films;
	for (map<string, vector<string>>::iterator i = FilmRole.begin(); i != FilmRole.end(); i++)
	{
		Films.push_back(i->first);
	}
	return Films;
}
