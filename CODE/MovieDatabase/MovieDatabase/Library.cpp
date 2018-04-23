#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "Library.h"


string GetDate(string Date)
{
	string yr = Date.substr(6, 4);
	string month = Date.substr(3, 2);
	string day = Date.substr(0, 2);
	return (yr + month + day);
}

string PrintDate(string Date)
{
	string yr = Date.substr(0, 4);
	string month = Date.substr(4, 2);
	string day = Date.substr(6, 2);
	return (day + "/" + month + "/" + yr);
}

vector<string> AddTokens(string Line)
{
	vector<string> temp;
	string TokenizedData;
	stringstream LineOfData(Line);
	while (getline(LineOfData, TokenizedData, ',')) //getting data
	{
		try {
			if (TokenizedData.substr(1, 1) == ",") { continue; }
			else temp.push_back(TokenizedData);
		}
		catch (exception e) {}
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

void PrintTable()
{
	char Cross = 197;
	char Edge = 196;
	char Last = 180;
	const int MaxTitleLength = 35;
	const int MaxGenreLength = 20;
	char Border = 179;

	for (int i = 0; i < 6; i++) { cout << Edge; } cout << Cross;
	for (int i = 0; i < MaxTitleLength + 3; i++) { cout << Edge; } cout << Cross;
	for (int i = 0; i < MaxGenreLength + 6; i++) { cout << Edge; } cout << Cross;
	for (int i = 0; i < 10; i++) { cout << Edge; } cout << Cross;
	for (int i = 0; i < 10; i++) { cout << Edge; } cout << Cross;
	for (int i = 0; i < 18; i++) { cout << Edge; } cout << Cross;
	for (int i = 0; i < 12; i++) { cout << Edge; } cout << Last;
	for (int i = 0; i < 18; i++) { cout << Edge; } cout << Last << endl;
}

string GetGender(string number)
{
	string Gender;
	if (number == ("1")) Gender = "Female";
	else if (number == ("2")) Gender = "Male";
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