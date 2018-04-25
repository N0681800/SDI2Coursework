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
	const int MaxNameLength = 25;
	const int MaxFilmLength = 40;
	char Border = 179;

	cout << setw(7) << left << ID << Border;
	cout << setw(MaxNameLength + 3) << left << Name << Border;
	cout << setw(10) << left << GetGender(Gender) << Border;
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
