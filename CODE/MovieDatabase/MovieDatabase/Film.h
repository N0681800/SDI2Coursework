#pragma once
#include <string>
#include <vector>
using namespace std;



class Film
{
private:
	string Input; //Line of Data from database to be split up

	struct Material
	{
		struct FrameAspect
		{
			int w;
			int h;

			string Disp()
			{
				return w + ":" + h;
			}
			void SetFA(string Input)
			{
				string Data;
				stringstream LineOfData(Input);
				getline(LineOfData, Data, '/'); //getting data
				w = stoi(Data);
				getline(LineOfData, Data, '/');
				h = stoi(Data);
			}
		};

		struct Price
		{
			int Dollars;
			int Cent;

			void setPrice(string Input)
			{
				string Data;
				stringstream LineOfData(Input);
				getline(LineOfData, Data, '.'); //getting data
				Dollars = stoi(Data);
				getline(LineOfData, Data, '.');
				Cent = stoi(Data);
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

		Price Cost;

		FrameAspect FA;

		Material(string Info)
		{
			string TokenizedData, TempData[8]; int i = 0;
			vector<string> TempInfo;
			stringstream LineOfData(Info);
			while (getline(LineOfData, TokenizedData, ',')) //getting data
			{
				TempInfo.push_back(TokenizedData); //Store data in temp array
				i++;
			}
			Format = 



		}

		void VHS(string Info)
		{
			Format = 0;

			string TokenizedData, TempData[8]; int i = 0;
			stringstream LineOfData(Info);
			while (getline(LineOfData, TokenizedData, '/')) //getting data
			{
				TempData[i] = TokenizedData; //Store data in temp array
				i++;
			}

			ID = TempData[0];
			Title = TempData[1];
			AudioFormat = TempData[2];
			Cost.setPrice(TempData[3]);
			FA.SetFA(TempData[4]);
			AudioLanguages = AddTokens(TempData[5]);
			SubtitleLanguages = AddTokens(TempData[6]);
		}

		void DVD(string Info)
		{
			Format = 1;
		}

		void dsDVD(string Info)
		{
			Format = 2;
		}

		void BluRay(string Info)
		{
			Format = 3;
		}

		void CBS(string Info)
		{
			Format = 4;
		}

		void PrintInfo()
		{

		}

	};
	

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


	vector<Material> Materials;
	int Runtime;
	vector<string> Languages;

	
	Film(string Input_);
	
	~Film();
	
	void Setup();//Loads in Data

	void Overview();//Prints out all info of a chosen film

	void Details();//Prints out basic data for database

	string getStatus();
};


