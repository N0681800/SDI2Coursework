#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class CastCrew
{
public:
	CastCrew(string filmID, string Details, bool isCast);

	~CastCrew();

	bool isCast;

	string ID;

	string Gender;

	string Name;

	std::map<string, string> FilmRole;


	void AddFilm(string FilmID, string Role);
private:


};

CastCrew::CastCrew(string filmID, string Details, bool isCast_)
{
	isCast = isCast_;

}
void CastCrew::AddFilm(string FilmID, string Role)
{
	

}
