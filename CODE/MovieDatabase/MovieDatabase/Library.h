#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;


//CHARACTERS FOR DRAWINGTABLES
const char BOX = 178;
const char BORDER = 179;
const char LAST = 180;
const char EDGE = 196;
const char CROSS = 197;
//MAX COLUMN WIDTHS FOR CERTAIN VALUES
const int MAX_NAME_LENGTH = 28;
const int MAX_FILM_LENGTH = 43;
const int MAX_TITLE_LENGTH = 38;
const int MAX_GENRE_LENGTH = 26;
const int MAX_MATERIAL_LENGTH = 15;
//COLUMN INFO FOR FILMS AND ACTORS
struct ColumnStructure{
	string Name;
	int Width;
};

const vector<ColumnStructure> ACTOR_TABLE = { 
	{"ID",7},{"Name",MAX_NAME_LENGTH},{"Gender",10},{"Films",MAX_FILM_LENGTH} };

const vector<ColumnStructure> FILM_TABLE = { 
	{"ID", 6}, { "Title",MAX_TITLE_LENGTH }, { "Genre",MAX_GENRE_LENGTH }, { "Date",10 }, { "Runtime",10 }, 
{ "Box Office Gross",18 }, { "Stats",12 }, { "Materials",MAX_MATERIAL_LENGTH }};


//Splits Line into mutliple strings by chosen Deliminator
vector<string> AddTokens(string Line,char Delim);

string PrintDate(int Date);

string ToLower(string Word);

string VectorAsString(vector<string> Vector);
//Sets legnth of string to stop overflow
string SetLength(string Input, int Max);

void PrintTable(vector<ColumnStructure> Vector);

string GetGender(int number);

bool InputChecker(string Choice, vector<string> legalChoices);

void PrintTableHeader(vector<ColumnStructure> Vector);