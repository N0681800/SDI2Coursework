#pragma once
#include "Film.h"
//#include "CastCrewClass.h"
#include <vector>
#include <string>
using namespace std;


class Database
{
public:

	string CURRENT_SORT;

	string CURRENT_SORT_TYPE;

	vector<Film> Storage; //Contains all films from database

	vector<Film*> Results; //A temp vector for search results

	//vector<CastCrew> ccStorage;

	Database(string filmPath, string ccPath, string matPath, int Max);

	~Database();

	void PrintResults(string Order);//Prints out details of a number of films

	void Search(string SearchField, string Query, char Order);//Searchs field for a value

	bool SaveData();//Saves the database

	void createNewTree(string SortBy);

	template <class T>
	T* Find(string ID, vector<T> *Vec);

	void PrintResultsVector();

private:

	string Username = "Admin", Password = "root";

	bool LoggedIn = false;

	class BinaryTree
	{
	public:
		BinaryTree();

		vector<Film*> Films;

		void Insert(Film *$Film, string toCompare);

		void printTree(string Order);

		void SearchFilm(string toSearch, string Find,char Order);

		int getSize();

		void Delete();

	private:
		struct TreeNode
		{
			Film *FilmInfo;
			TreeNode *Left;
			TreeNode *Right;
		};

		TreeNode * Root; // = new TreeNode;

		void SearchTree(TreeNode* Node, string toSearch, int toFind,char Parameter);

		void insertInt(TreeNode *Node, Film *toAdd, string toSort);

		void insertString(TreeNode *Node, Film *$Film, string toSort);

		void Print(TreeNode *Node, string Order);

		void DeleteNode(TreeNode *Node);

		int Size(TreeNode* Node);

	};

	BinaryTree Tree;

	string filmPath; //Path to database

	string ccPath; //Path to cast crew database

	string matPath; //Path to material database

	void FilmSetup(int MAX);//Setups Database,input of #of films to be loaded

	void MaterialSetup(int MAX);

	//void CastCrewSetup(int MAX);

	//bool ccExists(string ID, bool isActor);

	string GenerateID();//Generates a unique ID when creating a new Film
};
