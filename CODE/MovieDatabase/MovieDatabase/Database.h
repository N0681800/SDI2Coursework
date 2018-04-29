#pragma once
#include "Film.h"
#include "ActorClass.h"
#include <vector>
#include <string>
using namespace std;

class Database
{
public:
	Database(string filmPath, string ccPath, string matPath, int Max);

	~Database();

	//MENU FUNCTIONS
	void ViewDatabase();

	void SearchDatabase();

	void AddFilm();

	void EditFilm();

	void DeleteFilm();

	void FilmInfo();

	void SearchActorDatabase();

	void ViewActorDatabase();

	void ActorOverview();

	void LogIn();

private:
	//File Paths
	string filmPath;

	string ccPath;

	string matPath;

	string NEXT_ID = "000001";

	string Username = "Admin", Password = "root";

	bool LoggedIn = false;

	string CURRENT_SORT; string CURRENT_ACTOR_SORT;

	//Main Data Storage
	vector<Film> Storage;	
	
	vector<Actor> ActorStorage;

	class BinaryTree
	{
	public:
		vector<Film*> FilmResults;

		vector<Actor*> ActorResults;


		BinaryTree();

		vector<Film*> Films;

		void Insert(Film *$Film, string toCompare);

		void InsertActor(Actor *$Actor, string toCompare);

		int getSize();


		//Good
		void DeleteTree(string Tree);

		void TraverseActors(string Order);

		void TraverseFilms(string Order);

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
			ActorTreeNode *Left;
			ActorTreeNode *Right;
		};

		TreeNode* FilmRoot;

		ActorTreeNode* ActorRoot;

		void insertActorString(ActorTreeNode *Node, Actor *toAdd, string toSort);

		void insertInt(TreeNode *Node, Film *toAdd, string toSort);

		void insertString(TreeNode *Node, Film *$Film, string toSort);

		int Size(TreeNode* Node);

		//Good
		void DeleteFilmNode(TreeNode *Node);

		void DeleteActorNode(ActorTreeNode *Node);


		void TraverseActor(ActorTreeNode * Node, string Order);

		void TraverseFilm(TreeNode *Node, string Order);
	};

	BinaryTree Tree;

	void PrintFilmResults(string Order);//Prints out details of a number of films

	void Search(string SearchField, string Query, char Order);//Searchs field for a value

	void SearchActor(string Find, string type);

	bool SaveData();//Saves the database

	void createNewTree(string SortBy);

	void createActorTree(string SortBy);

	void PrintFilmVector();

	void PrintActorVector();

	void PrintFilmActors(vector<string> IDs, string FilmID);

	void MaterialDetails(Film* film);

	vector<string> GetFilms(string ActorID);

	string GetFilmName(string FilmID);

	vector<string> AddActors(string FilmID, string Input);

	void FilmSetup(int MAX);//Setups Database,input of #of films to be loaded

	void MaterialSetup(int MAX);

	void CastCrewSetup(int MAX);

	string SaveActors(Film f);

	void GenerateID();//Generates a unique ID when creating a new Film
};
