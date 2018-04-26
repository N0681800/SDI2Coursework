#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Library.h"


string PrintDate(int Date)
{
	return ((to_string(Date).substr(6, 2)) + "/" + (to_string(Date).substr(4, 2)) + "/" + (to_string(Date).substr(0, 4)));
}

vector<string> AddTokens(string Line, char Delim)
{
	vector<string> temp;
	string TokenizedData;
	stringstream LineOfData(Line);
	while (getline(LineOfData, TokenizedData, Delim)) //getting data
	{
		if (TokenizedData == "") temp.push_back("N/A");
		else temp.push_back(TokenizedData);
		/*
		try {
			if (TokenizedData.substr(1, 1) == ",") { continue; }
			else temp.push_back(TokenizedData);
		}
		catch (exception e) {}
		*/
	}
	return temp;
}

void PrintVector(vector<string> Vector)
{
	for (vector<string>::const_iterator i = Vector.begin(); i != Vector.end(); i++)
	{
		cout << *i;
		if (i != (Vector.end() - 1)) cout << ',';
	}
} //Can probs delete in future

string ToLower(string Word)
{
	for (int i = 0; Word[i]; i++) Word[i] = tolower(Word[i]);
	return Word;
}

string VectorAsString(vector<string> Vector)//Outputs a vector as a string used for searching
{
	string temp;
	for (vector<string>::const_iterator i = Vector.begin(); i != Vector.end(); i++)
	{
		temp += *i;
		if (i != (Vector.end() - 1)) temp += ',';
	}
	return temp;
}

string SetLength(string Input, int Max)
{
	string Word;
	if (Input.length() > (Max - 3)) Word = Input.substr(0, Max) + "...";

	else Word = Input;

	return Word;
}

void PrintTable(string Type)
{
	if (Type == "FILM")
	{
		for (int i = 0; i < 6; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < MAX_TITLE_LENGTH + 3; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < MAX_GENRE_LENGTH + 6; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < 10; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < 10; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < 18; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < 12; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < MAX_MATERIAL_LENGTH + 3; i++) { cout << EDGE; } cout << LAST << endl;
	}
	else
	{
		for (int i = 0; i < 7; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < MAX_NAME_LENGTH + 3; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < 10; i++) { cout << EDGE; } cout << CROSS;
		for (int i = 0; i < MAX_FILM_LENGTH + 3; i++) { cout << EDGE; } cout << LAST << endl;
	}
}

void PrintTableFromVector(vector<int> Columns)
{
	for (int i : Columns)
	{
		for (int j = 0; j < i; j++)
		{
			cout << EDGE;
		}
		if (i != Columns.size() - 1) cout << CROSS;
		else cout << LAST;
	}
	cout << endl;
}

string GetGender(int number)
{
	string Gender;
	if (number == (1)) Gender = "Female";
	else if (number == (2)) Gender = "Male";
	else Gender = "Unknown";
	return Gender;
}

bool InputChecker(string Choice, vector<string> legalChoices)
{
	try {

		if (find(legalChoices.begin(), legalChoices.end(), Choice) != legalChoices.end())
		{
			return true;
		}
		else
		{
			throw 10;
		}
	}
	catch (int a)
	{
		cout << "Sorry that is an invalid input" << endl;
		return false;
	}

}

void PrintTableHeader(string Type)
{
	char Border = 179;
	if (Type == "FILM")
	{
		const int MaxTitleLength = 35;
		const int MaxGenreLength = 20;
		const int MaxMaterialLength = 15;
		
		cout << setw(6) << left << "ID" << Border;
		cout << setw(MaxTitleLength + 3) << left << "Title" << Border;
		cout << setw(MaxGenreLength + 6) << left << "Genres" << Border;
		cout << setw(10) << left << "Released" << Border;
		cout << setw(10) << left << "Runtime" << Border;
		cout << setw(18) << left << "Box Office Sales" << Border;
		cout << setw(12) << left << "Status" << Border;
		cout << setw(MaxMaterialLength + 3) << left << "Avalible Materials" << Border << endl;

		
	}
	else
	{
		const int MaxNameLength = 25;
		const int MaxFilmLength = 40;
		//ID,Gender,Name,FIlms
		cout << setw(7) << left << "ID" << Border;
		cout << setw(MaxNameLength + 3) << left << "Name" << Border;
		cout << setw(10) << left << "Gender" << Border;
		cout << setw(MaxFilmLength + 3) << left << "Films" << Border<<endl;
	}

	PrintTable(Type);
}

template <typename T>
bool VectorCheck(vector<T> v)
{
	try {
		if (v.size() == 0)
		{
			throw 100;
		}
		else
		{
			return true;
		}
	}
	catch (int a)
	{
		return false;
	}
}