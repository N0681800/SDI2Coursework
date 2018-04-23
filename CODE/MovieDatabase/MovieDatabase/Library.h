#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//Used for drawing table
//const int MaxTitleLength = 35;
//const int MaxGenreLength = 20;
//char Border = 179;

//When tokenized strings contain more CSV this will get each indivudual one
vector<string> AddTokens(string Line);

void PrintVector(vector<string> Vector);

string GetDate(string Date);

string PrintDate(string Date);

string ToLower(string Word);

string VectorAsString(vector<string> Vector);

string SetLength(string Input, int Max);

void PrintTable();

string GetGender(string number);

bool InputChecker(string Choice, vector<string> legalChoices);
