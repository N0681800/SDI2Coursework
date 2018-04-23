#pragma once
#include <string>
#include <vector>
using namespace std;

class Film
{
private:
	string Input; //Line of Data from database to be split up
public:
	//All relevant Film Info

	string ID;
	string Title;
	vector<string> Genres;
	string Summary;
	vector<string> ProdComps;
	vector<string> Locations;
	string ReleaseDate;
	int Revenue;
	int Status;

	vector<string> Materials;
	int Runtime;
	vector<string> Languages;

	//map<string, string> StatusID = { {"0","Released"} ,{"1","Now Playing"},{"2","Unreleased"} };

	Film(string Input_);
	
	~Film();
	
	void Setup();//Loads in Data

	void Overview();//Prints out all info of a chosen film

	void Details();//Prints out basic data for database

	string getStatus();
};


