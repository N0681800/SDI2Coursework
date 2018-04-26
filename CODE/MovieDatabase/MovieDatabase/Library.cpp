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
	}
	return temp;
}


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
	if (Input.length() > Max)
	{
		return Input.substr(0, Max - 3) + "...";
	}
	else
	{
		return Input;
	}
}

void PrintTable(vector<ColumnStructure> Vector)
{
	for (vector<ColumnStructure>::iterator i = Vector.begin();i!=Vector.end();i++)
	{
		for (int j = 0; j < i->Width; j++)
		{
			cout << EDGE;
		}
		if (i != (Vector.end()) - 1) cout << CROSS;
		else cout << LAST;
	}
	cout << endl;
}

void PrintTableHeader(vector<ColumnStructure> vector)
{
	for (ColumnStructure S : vector)
	{
		cout << setw(S.Width) << left << S.Name << BORDER;
	}
	cout << endl;
	PrintTable(vector);
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