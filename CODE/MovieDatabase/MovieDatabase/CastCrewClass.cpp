#pragma once
#include "Library.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include "CastCrewClass.h"

using namespace std;

Cast::Cast(string FilmID, string Info)
{
	vector<string> split;
	int i = 0;
	split = AddTokens(Info, ',');
	i = split.size();
	if (i>1)
		Gender = GetGender(split[1]);
	if (i>2)
		ID = split[2];
	if (i>3)
		Name = split[3];
	if (i>0)
	AddFilm(FilmID, split[0]);

}



Crew::Crew(string FilmID, string Info)
{
	vector<string> split;
	int i = 0;
	split = AddTokens(Info, ',');
	i = split.size();
	if (i>0)
		Gender = GetGender(split[0]);
	if (i>1)
		ID = split[1];
	if (i>3)
		Name = split[3];

}

void Crew::PrintDetails() {
	cout << Role << endl;
	cout << Gender << endl;
	cout << ID << endl;
	cout << Name << endl;
	cout << endl;
	for (map<string, vector<string> >::iterator i = FilmRole.begin(); i != FilmRole.end(); ++i) {
		cout << (*i).first << ": ";
		vector <string> PrintRole = (*i).second;
		for (unsigned j = 0; j < PrintRole.size(); j++) {
			cout << PrintRole[j] << " ";
		}

	}
}

void Cast::PrintDetails() {
		for (map<string, vector<string> >::iterator i = FilmRole.begin(); i != FilmRole.end(); ++i) {
			cout << (*i).first << ": ";
			vector <string> PrintRole = (*i).second;
			for (unsigned j = 0; j<PrintRole.size(); j++) {
				cout << PrintRole[j] << " ";
			}
			cout << endl;
		}
	
	cout << Character << endl;
	cout << Gender << endl;
	cout << ID << endl;
	cout << Name << endl;
	cout << endl;


}

void Cast::AddFilm(string FilmID,string Character) {
	FilmRole[FilmID].push_back(Character);
}

void Crew::AddFilm(string FilmID, string Role) {
	FilmRole[FilmID].push_back(Role);
}
