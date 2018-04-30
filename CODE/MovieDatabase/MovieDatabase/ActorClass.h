#include "Library.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

class Actor
{
public:
	Actor(string FilmID,vector<string> Info);

	string ID;

	string Name;

	void AddFilm(string ID, string Character);

	string Save(string ID);

	string GetRole(string ID);

	void Details();

	bool DeleteFilm(string FilmID);

	vector<string> ReturnFilmIDs();

	int Gender;

	std::map<string, vector<string>> FilmRole;
};
