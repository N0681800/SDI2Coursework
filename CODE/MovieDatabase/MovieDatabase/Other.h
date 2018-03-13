#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "DatabaseClass.h"
#include "ProjectClass.h"

using namespace std;

//Functions
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
