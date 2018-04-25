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

void Actor::PrintDetails() {
		for (map<string, vector<string> >::iterator i = FilmRole.begin(); i != FilmRole.end(); ++i) {
			cout << (*i).first << ": ";
			vector <string> PrintRole = (*i).second;
			for (unsigned j = 0; j<PrintRole.size(); j++) {
				cout << PrintRole[j] << " ";
			}
			cout << endl;
		}
	cout << Gender << endl;
	cout << ID << endl;
	cout << Name << endl;
	cout << endl;


}

string Actor::GetRole(string ID)
{
	return VectorAsString(FilmRole[ID]);
}

string Actor::Save(string ID)
{
	return GetRole(ID) + "," + to_string(Gender) + "," + ID + "," + Name;
}

void Actor::AddFilm(string FilmID,string Character) {
	FilmRole[FilmID].push_back(Character);
}

