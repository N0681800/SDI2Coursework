﻿#pragma once
#include "Library.h"
#include <string>
#include <vector>
using namespace std;



class Film
{
private:
	

public:
	//All relevant Film Info
	struct Material
	{
		int Format; //0-VHS 1-DVD 2-dsDVD 3-ComboBoxSet 4-BluRay

		string ID; //Material notation + filmID

		vector<string> AudioLanguages; //VHS Can only have one

		vector<string> SubtitleLanguages; //VHS doeesn't have

		string Title; //Film name, or film name + Directors Cut, Extended Editon.

		string AudioFormat; //Mono,Stereo,Surround Sound

		string SideOneInfo; //For dsDVD

		string SideTwoInfo; //For dsDVD

		string getFormat();

		string Cost;

		string FA;

		Material(string Info);

		string SaveInfo();

	};

	string ID;
	string Title;	
	string Summary;

	vector<string> Genres;
	vector<string> ProdComps;
	vector<string> Locations;
	vector<string> Languages;

	int Runtime;
	int ReleaseDate;
	int Revenue;
	int Status;

	vector<Material> Materials;
	
	Film(string Input_);

	~Film();

	void Overview();//Prints out all info of a chosen film

	void Details();//Prints out basic data for database

	string Save();

	string SaveMaterials();

	string getStatus();

	string printMaterials();

};


