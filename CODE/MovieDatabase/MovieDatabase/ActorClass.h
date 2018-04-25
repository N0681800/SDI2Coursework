#include "Library.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>

class Actor
{
public:
	Actor(string FilmID,vector<string> Info);

	string ID;

	int Gender;

	string Name;

	std::map<string, vector<string>> FilmRole;

	void PrintDetails();

	void AddFilm(string ID, string Character);

	string Save(string ID);

	string GetRole(string ID);

	void Details();

	vector<string> ReturnFilmIDs();
private:


};
