#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Library.h"


string PrintDate(int Date)
{
	return ((to_string(Date).substr(6, 2)) + "/" + (to_string(Date).substr(4, 2)) + "/" + (to_string(Date).substr(0, 4)));
}

//Splits data seperated by a chosen delimintor and returns it as a vector
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

//Outputs a vector as a string used for searching
string VectorAsString(vector<string> Vector)
{
	string temp;
	for (vector<string>::const_iterator i = Vector.begin(); i != Vector.end(); i++)
	{
		temp += *i;
		if (i != (Vector.end() - 1)) temp += ',';
	}
	return temp;
}

//Sets max legnth of a word
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

//Printing tables from custom column structures
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

string PrintMenu(vector<string> Choices)
{
	PrintDivider();
	int i = 1;
	vector<string> Inputs;
	for (vector<string>:: iterator Choice = Choices.begin(); Choice != Choices.end(); Choice++)
	{
		cout << "\n" << i << " - " << *Choice << endl;
		Inputs.push_back(to_string(i));
		i++;
	}
	string Input; cout << "\nChoice : ";
	getline(cin, Input);
	while (!(find(Inputs.begin(), Inputs.end(), Input) != Inputs.end()))
	{
		int i = 1;
		cout << "\nSorry that is not a valid choice\nPlease Try again\nChoice :  " << endl;
		getline(cin, Input);

		for (vector<string>::iterator Choice = Choices.begin(); Choice != Choices.end(); Choice++)
		{
			cout <<"\n"<< i << " - " << *Choice << endl;
			i++;
		}
	}
	return Input;
}

int GetIntInput()
{
	while (true)
	{
		string input; int number;
		getline(cin, input);
		stringstream Stream(input);
		if (Stream >> number)
		{
			return number;
		}
		cout << "Sorry that was not a valid input. \nPlease try again." << endl;
	}
}

string GetStrInput()
{
	string input;
	getline(cin, input);
	while (input.empty())
	{
		cout << "Cannot be blank.\nPlease Try again : \n " << endl;
		getline(cin, input);
	}
	return input;
}

vector<string> GetVectorInputs()
{
	vector<string> Inputs;
	string Input;
	while (true)
	{
		cout << "Enter a item or type 'Return' to quit" << endl;
		Input = GetStrInput();
		if (Input == "Return")
		{
			if (Inputs.size() != 0)
			{
				return Inputs;
			}
			else
			{
				cout << "Cannot be empty\nPlease Try again : \n " << endl;
			}
		}
		else
		{
			Inputs.push_back(Input);
		}
	}
}

void PrintDivider()
{
	for (int i = 0; i < 50; i++)
	{
		cout << EDGE;
	}
	cout << endl;
}


string GetFormatCode(int Format)
{
	switch (Format)
	{
	case 0:
		return "VHS";
	case 1:
		return "DVD";
	case 2:
		return "DSDvD";
	case 3:
		return "CBS";
	case 4:
		return "BluRay";
	default:
		return NULL;
	}
}