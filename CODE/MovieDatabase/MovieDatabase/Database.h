#pragma once
#include "Film.h"
#include "ActorClass.h"
#include <vector>
#include <string>
using namespace std;


class Database
{
public:

	string CURRENT_SORT;

	string CURRENT_SORT_TYPE;

	vector<Film> Storage; //Contains all films from database

	vector<Actor> ActorStorage;

	vector<Film*> Results; //A temp vector for search results

	vector<Actor*> ActorResults;

	//vector<CastCrew> ccStorage;

	Database(string filmPath, string ccPath, string matPath, int Max);

	~Database();

	void PrintResults(string Order);//Prints out details of a number of films

	void PrintActors(string Order);

	void Search(string SearchField, string Query, char Order);//Searchs field for a value

	void SearchActor(string Find, string type);

	void SearchActorName(string Find);

	void SearchActorFilms(int Find);

	bool SaveData();//Saves the database

	void createNewTree(string SortBy);

	void PrintResultsVector();

	void PrintActorVector();

	vector<string> GetFilms(string ActorID);

	string GetFilmName(string FilmID);

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

		int getSize();

		void Delete();

	private:
		struct TreeNode
		{
			Film *FilmInfo;
			TreeNode *Left;
			TreeNode *Right;
		};

		struct ActorTreeNode
		{
			Actor *ActorInfo;
			TreeNode *Left;
			TreeNode *Right;
		};

		TreeNode * Root; // = new TreeNode;

		//void SearchTree(TreeNode* Node, string toSearch, int toFind,char Parameter);

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

	vector<string> AddActors(string FilmID, string Input);

	void FilmSetup(int MAX);//Setups Database,input of #of films to be loaded

	void MaterialSetup(int MAX);

	void CastCrewSetup(int MAX);

	string SaveActors(Film f);

	//void CastCrewSetup(int MAX);

	//bool ccExists(string ID, bool isActor);

	string GenerateID();//Generates a unique ID when creating a new Film
};
