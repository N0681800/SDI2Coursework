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

vector<Cast> CheckCast;

vector<Crew> CheckCrew;

template <class T>
T* Find(string ID, vector<T> *Vec)
{
	int start = 0, end = Vec->size() - 1;
	while (start <= end)
	{
		int M = floor(((end - start) / 2));

		if (Vec->at(M).ID == ID)
		{
			return &Vec->at(M);
		}
		if (Vec->at(M).ID < ID)
		{
			start = M - 1;
		}
		else
		{
			end = M - 1;
		}
	}
	return NULL;
}

void SetUp()
{
	ifstream FromFile("CastCrew.txt");
	if (FromFile.is_open()) cout << "\nFile sucessfully Loaded!\n" << endl;
	int j = 0;
	string Data1;
	while (getline(FromFile, Data1)) //getting data
	{
		vector<string> TempData;
		vector<string> ReadID, ReadCast, ReadCrew,GetCrew;
		TempData =AddTokens(Data1, '|');
		ReadCast = AddTokens(TempData[1], '/');
		ReadCrew = AddTokens(TempData[2], '/');
int q = 0;
			for (vector<string>::iterator k = ReadCrew.begin(); k != ReadCrew.end(); k++) {
				
				GetCrew = AddTokens(ReadCrew[q], ',');
				//for (vector<string>::iterator j = GetCrew.begin(); j != GetCrew.end(); j++)
				//{
					//check if in vector
					// getcrew[1] is the actor id
					//TempData[0] is the film id
					Crew* pointer = Find(GetCrew[1], &CheckCrew);
					if (pointer) {
						pointer->AddFilm(TempData[0], GetCrew[2]);
					}
					else {
						Crew CrewTemp(TempData[0], VectorAsString(GetCrew));
						CrewTemp.AddFilm(TempData[0], GetCrew[2]);
						CheckCrew.push_back(CrewTemp);
					}
				//}
				q++;
			}
		
		
		for (vector<string>::iterator i = ReadCast.begin(); i != ReadCast.end(); i++)
		{
			Cast Temp(TempData[0], *i);
			CheckCast.push_back(Temp);
		}
		j++;
		if (j == 10) {
			break;
		}
	}
}


	int main() {
		SetUp();
		PrintTable();
		for (vector<Cast>::iterator i = CheckCast.begin(); i != CheckCast.end();i++)
		{
			//i->PrintDetails();
		}
		
		cout << "///////////////////////////////////////////////////////" << endl;
		
		for (vector<Crew>::iterator i = CheckCrew.begin(); i != CheckCrew.end(); i++)
		{
			i->PrintDetails();
		}

		cout << "loaded";
		getchar();
		getchar();
		return 0;

	}