#pragma once
#include "Library.h"
#include <string>
#include <vector>
using namespace std;



class Film
{
private:
	string Input; //Line of Data from database to be split up

public:
	//All relevant Film Info
	struct Material
	{
		struct FrameAspect
		{
			int w;
			int h;

			string Disp();

			void SetFA(string Input);
		};

		struct Price
		{
			int Dollars;
			int Cent;

			void setPrice(string Input);

			string asString()
			{
				return Dollars + "." + Cent;
			}

		};

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

		//Price Cost;

		string FA;
		//FrameAspect FA;

		Material(string Info);

		string SaveInfo();


	};

	string ID;
	string Title;
	vector<string> Genres;
	string Summary;
	vector<string> ProdComps;
	vector<string> Locations;
	string ReleaseDate;
	int Revenue;
	int Status;


	vector<Material> Materials;
	int Runtime;
	vector<string> Languages;


	Film(string Input_);

	~Film();

	void Setup();//Loads in Data

	void Overview();//Prints out all info of a chosen film

	void Details();//Prints out basic data for database

	void Save();

	string getStatus();

	string printMaterials();

};


