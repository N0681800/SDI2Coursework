#include "Library.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>

class Cast
{
public:
	Cast(string FilmID, string Info);

	string Character;

	string ID;

	string Gender;

	string Name;

	std::map<string, vector<string>> FilmRole;

	void PrintDetails();
	void AddFilm(string ID, string Character);
private:


};

class Crew
{
public:
	Crew(string FilmID, string Info);

	string Role;

	string ID;

	string Gender;

	string Name;

	void PrintDetails();
	void AddFilm(string ID, string Role);

	std::map<string, vector<string>> FilmRole;

private:


};
