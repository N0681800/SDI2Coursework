#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Film.h"
#include "Library.h"
#include "Database.h"
using namespace std;

/*
class CastCrew
{
public:
	CastCrew(string ID_, string Name_, string Gender_, bool isCast_);

	//~CastCrew();

	bool isCast;

	string ID;

	string Gender;

	string Name;

	std::map<string, string> FilmRole;

	void AddFilm(string FilmID, string Role);

	//void PrintRole(string FilmID);

	void PrintDetails();

private:


};

CastCrew::CastCrew(string ID_,string Name_,string Gender_,bool isCast_)
{
	ID = ID_;
	Name = Name_;
	Gender = Gender_;
	isCast = isCast_;
}

void CastCrew::PrintDetails()
{
	cout << "ID: " << ID;
	cout << "Name: " << Name;
	cout << "Gender: " << Gender;
	cout << "Films: " << FilmRole[0] << endl;
}
/*
void CastCrew::PrintRole(string FilmID)
{
	cout << "Film: " << /GetFilmTitle(FilmID) << endl;
	cout << "Role: " << FilmRole[FilmID] << endl;
}

void CastCrew::AddFilm(string FilmID, string Role)
{
	FilmRole[FilmID] = Role;
}

*/