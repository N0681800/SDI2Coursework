#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;



const map<int, string> Exceptions = { {1,"Invalid Input"},{ 2,"Line not read" },{ 3,"Film could not be found" },
{4,"Insuffcient Info"} };
//CHARACTERS FOR DRAWINGTABLES
const unsigned char BOX = 178;
const unsigned char BORDER = 179;
const unsigned char LAST = 180;
const unsigned char EDGE = 196;
const unsigned char CROSS = 197;
//MAX COLUMN WIDTHS FOR CERTAIN VALUES
const int MAX_NAME_LENGTH = 28;
const int MAX_FILM_LENGTH = 43;
const int MAX_TITLE_LENGTH = 38;
const int MAX_GENRE_LENGTH = 26;
const int MAX_MATERIAL_LENGTH = 15;
const int MAX_ROLE_LENGTH = 30;
//COLUMN INFO FOR FILMS AND ACTORS
struct ColumnStructure{
	string Name;
	int Width;
};

const vector<ColumnStructure> ACTOR_TABLE = { 
	{"ID",7},{"Name",MAX_NAME_LENGTH},{"Gender",10},{"Films",MAX_FILM_LENGTH} };

const vector<ColumnStructure> ACTOR_FILM_TABLE = {
	{ "Name",MAX_NAME_LENGTH },{ "Gender",10 },{ "Role",MAX_ROLE_LENGTH } };

const vector<ColumnStructure> FILM_TABLE = { 
	{"ID", 6}, { "Title",MAX_TITLE_LENGTH }, { "Genre",MAX_GENRE_LENGTH }, { "Date",10 }, { "Runtime",10 }, 
{ "Box Office Gross",18 }, { "Status",12 }, { "Materials",MAX_MATERIAL_LENGTH }};

const vector<ColumnStructure> CREW_TABLE = {
	{ "Name",MAX_NAME_LENGTH },{ "Gender",10 },{ "Roles",40 } };

//Splits Line into mutliple strings by chosen Deliminator
vector<string> AddTokens(string Line,char Delim);

string PrintDate(int Date);

string ToLower(string Word);

string VectorAsString(vector<string> Vector);
//Sets legnth of string to stop overflow
string SetLength(string Input, int Max);

void PrintTable(vector<ColumnStructure> Vector);

string GetGender(int number);

void PrintTableHeader(vector<ColumnStructure> Vector);

string PrintMenu(vector<string> Choices);

int GetIntInput();

string GetStrInput();

vector<string> GetVectorInputs();

void PrintDivider();
