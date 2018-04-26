#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;


//For table drawing
const char BORDER = 179;
const char CROSS = 197;
const char EDGE = 196;
const char LAST = 180;

const int MAX_NAME_LENGTH = 25;
const int MAX_FILM_LENGTH = 40;
const int MAX_TITLE_LENGTH = 35;
const int MAX_GENRE_LENGTH = 20;
const int MAX_MATERIAL_LENGTH = 15;

const vector<int> ACTOR_TABLE = { 7,MAX_NAME_LENGTH + 3,10,MAX_FILM_LENGTH +3 };


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

void PrintTable(string type);

string GetGender(int number);

bool InputChecker(string Choice, vector<string> legalChoices);

void PrintTableHeader(string Type);

void PrintTableFromVector(vector<int> Columns);

template <typename T>
bool VectorCheck(vector<T> v);