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
vector<string> AddTokens(string Line,char Delim);

void PrintVector(vector<string> Vector);

string PrintDate(int Date);

string ToLower(string Word);

string VectorAsString(vector<string> Vector);

string SetLength(string Input, int Max);

void PrintTable();

string GetGender(string number);

bool InputChecker(string Choice, vector<string> legalChoices);

template <typename T>
bool VectorCheck(vector<T> v);