#include "Database.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <vector>
#include <map>
#include <sstream>

#include "Library.h"
#include "Templates.cpp"



//SETUP
Database::Database(string filmPath_, string ccPath_,string matPath_, int Max)
{
	filmPath = filmPath_;
	ccPath = ccPath_;
	matPath = matPath_;

	FilmSetup(Max);
	getchar();

	MaterialSetup(Max);
	getchar();

	CastCrewSetup(Max);
	createNewTree("5");
}

Database::~Database()
{
	if (SaveData())
	{
		cout << "Save Successful" << endl;
	}
	else
	{
		cout << "Save failed." << endl;
	}

	cout << "Press Enter to quit." << endl;
	getchar();
}

void Database::FilmSetup(int MAX)
{
	string Line;
	ifstream FromFile(filmPath);

	if (FromFile.is_open()) cout << "\nFile sucessfully Loaded!\n" << endl;

	while (getline(FromFile, Line))
	{
		Storage.push_back(Film(Line));

		if (Storage.size() == MAX) break;
	}

	cout << "\n"<< Storage.size() << " Films Loaded.\n" << endl;
}

void Database::MaterialSetup(int MAX)
{
	string Line;
	ifstream MaterialFile(matPath);
	if (MaterialFile.is_open()) cout << "\Materials sucessfully Loaded!\n" << endl;
	int n = 0;
	for (int i = 0; i < MAX; i++)
	{
		try
		{
			if (!getline(MaterialFile, Line))
			{
				throw(2);
			}
			else
			{
				vector<string> MaterialLine = AddTokens(Line, '|');

				try {
					Film* Pointer;
					if (!(Pointer = (Find(MaterialLine[0], &Storage))))
					{
						throw(3);
					}
					else
					{
						if (Pointer->Status == 0)
						{
							for (vector<string>::iterator i = MaterialLine.begin() + 1; i != MaterialLine.end(); i++)
							{
								Pointer->Materials.push_back(Film::Material(*i));
								n++;
							}
						}
					}
				}
				catch (int E)
				{
					continue;//Film does not exist skip over it
					cout << Exceptions.find(E)->second << endl;
				}
			}
		}
		catch (int E)
		{
			cout << Exceptions.find(E)->second << endl;
		}
	}
	cout << "\n" << n << " Materials Loaded.\n" << endl;
}

void Database::CastCrewSetup(int MAX)
{
	string Line;
	ifstream CastCrewFile(ccPath);
	if (CastCrewFile.is_open()) cout << "\CastCrew sucessfully Loaded!\n" << endl;
	int CrewN = 0;
	for (int i = 0; i < MAX; i++)
	{
		try
		{
			if (!getline(CastCrewFile, Line))
			{
				throw(2);
			}

			vector<string> CastCrewLine = AddTokens(Line, '|');

			while (CastCrewLine[0].length() < 7)
			{
				CastCrewLine[0] = "0" + CastCrewLine[0];
			}
			try {
				if (CastCrewLine.size() != 3)
				{
					throw(4);
				}
				Film* Pointer;
				if (!(Pointer = (Find(CastCrewLine[0], &Storage))))
				{
					throw(3);
				}
				else
				{
					CrewN += Pointer->AddCrew(CastCrewLine[2]);
					Pointer->CastIDs = AddActors(CastCrewLine[0], CastCrewLine[1]);
				}
			}
			catch (int E)
			{
				cout << Exceptions.find(E)->second << endl;
				continue;//Film does not exist skip over it
			}
		}
		catch (int E)
		{
			cout << Exceptions.find(E)->second<<endl;
		}
	}
	
	cout << "\n" << ActorStorage.size() << " Actors loaded.\n" << endl;
	cout << "\n" << CrewN << " Crew members loaded.\n" << endl;
}


void Database::PrintFilmResults(string Order)//Prints out details of a number of films
{
	Tree.TraverseFilms(Order);
	PrintFilmVector();
}

void Database::Search(string SearchField, string Query,char Order,vector<Film*> ToSearch,int Level)//Searchs field for a value
{

	if (Level == 0) Tree.FilmResults.clear();

	if (SearchField == "1" || SearchField == "2" || SearchField == "3" || SearchField == "4" || SearchField == "5")
	{
		map<string, string> SearchFields;

		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{

			SearchFields["1"] = i->Title;
			SearchFields["2"] = VectorAsString(i->Genres); SearchFields["3"] = VectorAsString(i->ProdComps);
			SearchFields["5"] = VectorAsString(i->Locations); SearchFields["4"] = VectorAsString(i->Languages);

			if ((ToLower(SearchFields[SearchField])).find(ToLower(Query)) != string::npos)
			{
				Tree.FilmResults.push_back(&*i);
			}
		}
		
		if (Tree.FilmResults.size() > 0)
		{
			PrintFilmVector();
		}

	}
	else if (SearchField == "6" || SearchField == "7" || SearchField == "8")
	{
		map<string, int> SearchFields;
		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{
			 
			SearchFields["6"] = i->Revenue; SearchFields["7"] = i->Runtime; SearchFields["8"] = i->ReleaseDate;
			if (Order == '>')
			{
				if (SearchFields[SearchField] >= stoi(Query))
				{
					Tree.FilmResults.push_back(&*i);
				}
			}
			else
			{
				if (SearchFields[SearchField] <= stoi(Query))
				{
					Tree.FilmResults.push_back(&*i);
				}
			}
		}
		
		if (Tree.FilmResults.size() > 0)
		{
			PrintFilmVector();
		}
	}
	else //Sort by status
	{
		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{
			if (i->Status == stoi(Query))
			{
				Tree.FilmResults.push_back(&*i);
			}
		}
		if (Tree.FilmResults.size() > 0)
		{
			PrintFilmVector();
		}
	}
}

void Database::SearchActor(string Value,string Type)
{
	Tree.ActorResults.clear();

	for (vector<Actor>::iterator i = ActorStorage.begin(); i != ActorStorage.end(); i++)
	{
		if (Type == "2")
		{
			if (to_string(i->FilmRole.size()) >= Value)
			{
				Tree.ActorResults.push_back(&*i);
			}
		}
		else
		{
			if (ToLower(i->Name).find(ToLower(Value)) != string::npos)
			{
				Tree.ActorResults.push_back(&*i);
			}
		}
	}
	PrintActorVector();
}



void Database::PrintFilmActors(vector<string> CastID,string Film)
{
	cout << "Actor Overview" << endl;

	PrintTableHeader(ACTOR_FILM_TABLE);
	for (string i : CastID)
	{
		Actor* Pointer = Find(i, &ActorStorage);
		cout << setw(MAX_NAME_LENGTH) << left << Pointer->Name << BORDER;
		cout << setw(10) << left << GetGender(Pointer->Gender) << BORDER;
		cout << setw(MAX_ROLE_LENGTH) << left << Pointer->GetRole(Film) << BORDER << endl;

		PrintTable(ACTOR_FILM_TABLE);
	}
}

vector<string> Database::GetFilms(string ActorID)
{
	vector<string> FilmNames;
	vector<string> FilmIds = Find(ActorID, &ActorStorage)->ReturnFilmIDs();
	
	for (vector<string>::iterator i = FilmIds.begin(); i != FilmIds.end(); i++)
	{
		FilmNames.push_back(GetFilmName(*i));
	}
	return FilmNames;
}

string Database::GetFilmName(string FilmID)
{
	return Find(FilmID, &Storage)->Title;
}

vector<string> Database::AddActors(string FilmID,string Input)
{
	vector<string> AllCast = AddTokens(Input, '/');
	vector<string> ActorIDs;
	for (vector<string>::iterator i = AllCast.begin(); i != AllCast.end(); i++)
	{
		vector<string> ActorInfo = AddTokens(*i, ',');
		try {
			if (ActorInfo.size() != 4)
			{
				throw 4;
			}
			else
			{
				while (ActorInfo[2].length() < 7)
				{
					ActorInfo[2] = "0" + ActorInfo[2];
				}

				Actor* ActorPointer;
				if (!(ActorPointer = Find(ActorInfo[2], &ActorStorage))) 
				{
					Actor Temp(FilmID, ActorInfo);
					vector<Actor>::iterator Index = (ActorStorage.begin() + InOrder(Temp, ActorStorage));
					ActorStorage.insert(Index, Temp);
					ActorIDs.push_back(ActorInfo[2]);
				}
				else
				{
					ActorPointer->AddFilm(FilmID, ActorInfo[0]);
					ActorIDs.push_back(ActorInfo[2]);
				}

			}
		}
		catch (int E)
		{
			cout << Exceptions.find(E)->second << endl;//Not enough info exception
		}
	}
	return ActorIDs;
}

void Database::GenerateID()
{
	int INT = 1;
	for (Film i : Storage)
	{
		if (NEXT_ID == i.ID)
		{
			INT++;
		}
	}
	NEXT_ID = to_string(INT);
	while (NEXT_ID.length() < 7)
	{
		NEXT_ID = "0" + NEXT_ID;
	}
}

string Database::SaveActors(Film f)
{
	string toSave;
	for (vector<string>::iterator i = f.CastIDs.begin(); i != f.CastIDs.end(); i++)
	{
		Actor* ActorPointer;
		string id = *i;
		ActorPointer = Find(id, &ActorStorage);
		toSave += ActorPointer->Save(f.ID);
		if (i != f.CastIDs.end() - 1)
		{
			toSave += "/";
		}
	}
	return toSave;
}

bool Database::SaveData()
{
	bool Saved = false;
	ofstream outFile(filmPath, ofstream::out);
	ofstream MaterialoutFile(matPath, ofstream::out);
	ofstream CastCrewoutFile(ccPath, ofstream::out);

	for (vector<Film>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Film Temp = *i; 
		outFile << Temp.Save() << endl;
		if (Temp.Materials.size() != 0)
		{
			MaterialoutFile << Temp.SaveMaterials() << endl;
		}
		CastCrewoutFile << Temp.ID + "|" + SaveActors(Temp) + "|" + Temp.SaveCrew() << endl;
	}

	outFile.flush();
	MaterialoutFile.flush();
	CastCrewoutFile.flush();

	Saved = true;

	outFile.close();
	MaterialoutFile.close();
	CastCrewoutFile.close();
	return Saved;
}

void Database::createNewTree(string SortBy)
{
	if (CURRENT_SORT != SortBy)
	{
		Tree.DeleteTree("FILM");
		CURRENT_SORT = SortBy;
		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{
				Tree.Insert(&*i, SortBy);
		}
	}
}

void Database::createActorTree(string SortBy)
{
	if (CURRENT_ACTOR_SORT != SortBy)
	{
		Tree.DeleteTree("ACTOR");
		CURRENT_ACTOR_SORT = SortBy;

		for (vector<Actor>::iterator i = ActorStorage.begin(); i != ActorStorage.end(); i++)
		{
			Tree.InsertActor(&*i, SortBy);
		}
	}
}

Database::BinaryTree::BinaryTree()
{
	FilmRoot = NULL;
	ActorRoot = NULL;
}

void Database::BinaryTree::Insert(Film *toAdd, string toSort)
{
	if (!FilmRoot)
	{
		FilmRoot = new TreeNode;
		FilmRoot->Left = NULL;
		FilmRoot->Right = NULL;
		FilmRoot->FilmInfo = toAdd;
	}
	else
	{
		if (toSort == "3" || toSort == "4" || toSort == "5" || toSort == "6")
		{
			insertInt(FilmRoot, toAdd, toSort);
		}
		else
		{
			insertString(FilmRoot, toAdd, toSort);
		}
	}
}

void Database::BinaryTree::insertInt(TreeNode *Node, Film *toAdd, string toSort)
{

	struct intPtr
	{
		int *Value;
		int *Node;
	};
	map<string, intPtr> Comparison;
	Comparison["3"] = { &toAdd->Revenue,&Node->FilmInfo->Revenue };
	Comparison["6"] = { &toAdd->Runtime,&Node->FilmInfo->Runtime };
	Comparison["5"] = { &toAdd->Status,&Node->FilmInfo->Status };
	Comparison["4"] = { &toAdd->ReleaseDate,&Node->FilmInfo->ReleaseDate };

	if (*Comparison[toSort].Value < *Comparison[toSort].Node)
	{
		if (!(Node->Left))
		{
			Node->Left = new TreeNode;
			Node->Left->Left = NULL;
			Node->Left->Right = NULL;
			Node->Left->FilmInfo = toAdd;
		}
		else
		{
			insertInt(Node->Left, toAdd, toSort);
		}
	}
	else if (*Comparison[toSort].Value > *Comparison[toSort].Node)
	{
		if (!(Node->Right))
		{
			Node->Right = new TreeNode;
			Node->Right->Left = NULL;
			Node->Right->Right = NULL;
			Node->Right->FilmInfo = toAdd;
		}
		else
		{
			insertInt(Node->Right, toAdd, toSort);
		}
	}
	
	else //Values Same, Defualt to Alphabeitcal Sort
	{
		//insertString(Node, toAdd, "TITLE");
		
		if (ToLower(*&toAdd->Title) < ToLower(*&Node->FilmInfo->Title))
		{
			if (!(Node->Left))
			{
				Node->Left = new TreeNode;
				Node->Left->Left = NULL;
				Node->Left->Right = NULL;
				Node->Left->FilmInfo = toAdd;
			}
			else
			{
				insertInt(Node->Left, toAdd, toSort);
			}
		}
		else if (ToLower(*&toAdd->Title) > ToLower(*&Node->FilmInfo->Title))
		{
			if (!(Node->Right))
			{
				Node->Right = new TreeNode;
				Node->Right->Left = NULL;
				Node->Right->Right = NULL;
				Node->Right->FilmInfo = toAdd;
			}
			else
			{
				insertInt(Node->Right, toAdd, toSort);
			}
		}
		
	}
	
}

void Database::BinaryTree::insertString(TreeNode *Node, Film *toAdd, string toSort)
{
	struct strPtr
	{
		string *Value;
		string *Node;
	};
	map<string, strPtr> Comparison;
	Comparison["1"] = { &toAdd->ID,&Node->FilmInfo->ID };
	Comparison["2"] = { &toAdd->Title,&Node->FilmInfo->Title };

	//ID,TITLE,ReleaseDate,Revenue,Runtime,Status



	if (ToLower(*Comparison[toSort].Value) < ToLower(*Comparison[toSort].Node))
	{
		if (!(Node->Left))
		{
			Node->Left = new TreeNode;
			Node->Left->Left = NULL;
			Node->Left->Right = NULL;
			Node->Left->FilmInfo = toAdd;
		}
		else
		{
			insertString(Node->Left, toAdd, toSort);
		}
	}
	else if(ToLower(*Comparison[toSort].Value) > ToLower(*Comparison[toSort].Node))
	{
		if (!(Node->Right))
		{
			Node->Right = new TreeNode;
			Node->Right->Left = NULL;
			Node->Right->Right = NULL;
			Node->Right->FilmInfo = toAdd;
		}
		else
		{
			insertString(Node->Right, toAdd, toSort);
		}
	}
	
	else //Values Same, Defualt to Alphabeitcal Sort
	{
		//insertString(Node, toAdd, "TITLE");

		if (ToLower(*&toAdd->Title) < ToLower(*&Node->FilmInfo->Title))
		{
			if (!(Node->Left))
			{
				Node->Left = new TreeNode;
				Node->Left->Left = NULL;
				Node->Left->Right = NULL;
				Node->Left->FilmInfo = toAdd;
			}
			else
			{
				insertString(Node->Left, toAdd, toSort);
			}
		}
		else if (ToLower(*&toAdd->Title) > ToLower(*&Node->FilmInfo->Title))
		{
			if (!(Node->Right))
			{
				Node->Right = new TreeNode;
				Node->Right->Left = NULL;
				Node->Right->Right = NULL;
				Node->Right->FilmInfo = toAdd;
			}
			else
			{
				insertString(Node->Right, toAdd, toSort);
			}
		}

	}
	
}

void Database::BinaryTree::InsertActor(Actor *$Actor, string toCompare)
{
	if (!ActorRoot)
	{
		ActorRoot = new ActorTreeNode;
		ActorRoot->Left = NULL;
		ActorRoot->Right = NULL;
		ActorRoot->ActorInfo = $Actor;
	}
	else
	{
		insertActorString(ActorRoot, $Actor, toCompare);
	}
}

void Database::BinaryTree::insertActorString(ActorTreeNode *ActorNode, Actor *toAdd, string toSort)
{
	struct strPtr
	{
		string *Value;
		string *Node;
	};
	string* size = &to_string(toAdd->FilmRole.size());

	map<string, strPtr> Comparison;
	Comparison["1"] = { &toAdd->ID,&ActorNode->ActorInfo->ID };
	Comparison["2"] = { &toAdd->Name,&ActorNode->ActorInfo->Name };
	Comparison["3"] = { &to_string(toAdd->FilmRole.size()),&to_string(ActorNode->ActorInfo->FilmRole.size()) };

	if (ToLower(*Comparison[toSort].Value) < ToLower(*Comparison[toSort].Node))
	{
		if (!(ActorNode->Left))
		{
			ActorNode->Left = new ActorTreeNode;
			ActorNode->Left->Left = NULL;
			ActorNode->Left->Right = NULL;
			ActorNode->ActorInfo = toAdd;
		}
		else
		{	
			insertActorString(ActorNode->Right, toAdd, toSort);
		}
	}
	else if (ToLower(*Comparison[toSort].Value) > ToLower(*Comparison[toSort].Node))
	{
		if (!(ActorNode->Right))
		{
			ActorNode->Right = new ActorTreeNode;
			ActorNode->Right->Left = NULL;
			ActorNode->Right->Right = NULL;
			ActorNode->Right->ActorInfo = toAdd;
		}
		else
		{
			insertActorString(ActorNode->Right, toAdd, toSort);
		}
	}

	else //Values Same, Defualt to Alphabeitcal Sort
	{
		//insertString(Node, toAdd, "TITLE");

		if (ToLower(*&toAdd->Name) < ToLower(*&ActorNode->ActorInfo->Name))
		{
			if (!(ActorNode->Left))
			{
				ActorNode->Left = new ActorTreeNode;
				ActorNode->Left->Left = NULL;
				ActorNode->Left->Right = NULL;
				ActorNode->Left->ActorInfo = toAdd;
			}
			else
			{
				insertActorString(ActorNode->Left, toAdd, toSort);
			}
		}
		else if (ToLower(*&toAdd->Name) > ToLower(*&ActorNode->ActorInfo->Name))
		{
			if (!(ActorNode->Right))
			{
				ActorNode->Right = new ActorTreeNode;
				ActorNode->Right->Left = NULL;
				ActorNode->Right->Right = NULL;
				ActorNode->Right->ActorInfo = toAdd;
			}
			else
			{
				insertActorString(ActorNode->Right, toAdd, toSort);
			}
		}

	}
}

int Database::BinaryTree::getSize()
{
	return Size(FilmRoot);
}

int Database::BinaryTree::Size(TreeNode* Node)
{
	if (!Node)
	{
		return 0;
	}
	else
	{
		int tree_size = Size(Node->Left) + Size(Node->Right) + 1;
		return tree_size;
	}
}


//SORTING AND PRINTING
//These traverse in order and add to results vector
void Database::BinaryTree::TraverseActors(string Order)
{
	ActorResults.clear();
	TraverseActor(ActorRoot, Order);
}

void Database::BinaryTree::TraverseFilms(string Order)
{
	FilmResults.clear();
	TraverseFilm(FilmRoot, Order);
}

void Database::BinaryTree::TraverseActor(ActorTreeNode *Node, string Order)
{
	if (!Node)
	{
		return;
	}
	if (Order == "1")
	{
		TraverseActor(Node->Left, Order);
		ActorResults.push_back(Node->ActorInfo);
		TraverseActor(Node->Right, Order);
	}
	else
	{
		TraverseActor(Node->Right, Order);
		ActorResults.push_back(Node->ActorInfo);
		TraverseActor(Node->Left, Order);
	}
}

void Database::BinaryTree::TraverseFilm(TreeNode *Node, string Order)
{
	if (!Node)
	{
		return;
	}
	if (Order == "1")
	{
		TraverseFilm(Node->Left, Order);
		FilmResults.push_back(Node->FilmInfo);
		TraverseFilm(Node->Right, Order);
	}
	else
	{
		TraverseFilm(Node->Right, Order);
		FilmResults.push_back(Node->FilmInfo);
		TraverseFilm(Node->Left, Order);
	}
}

void Database::PrintFilmVector()
{
	PrintTableHeader(FILM_TABLE);

	for (vector<Film*>::iterator i = Tree.FilmResults.begin(); i != Tree.FilmResults.end(); i++)
	{
		(*i)->Details();
	}
}

void Database::PrintActorVector()
{
	PrintTableHeader(ACTOR_TABLE);
	for (vector<Actor*>::iterator i = Tree.ActorResults.begin(); i != Tree.ActorResults.end(); i++)
	{
		(*i)->Details();

		cout << setw(MAX_FILM_LENGTH) << left << SetLength(VectorAsString(GetFilms((*i)->ID)), MAX_FILM_LENGTH) << BORDER << endl;

		PrintTable(ACTOR_TABLE);
	}
}

//Deletion
void Database::BinaryTree::DeleteTree(string Tree)
{
	if (Tree == "ACTOR") DeleteActorNode(ActorRoot);
	else DeleteFilmNode(FilmRoot);
}

void Database::BinaryTree::DeleteActorNode(ActorTreeNode *Node)
{
	if (Node)
	{
		DeleteActorNode(Node->Left);
		DeleteActorNode(Node->Right);
		if (Node != ActorRoot) delete Node;
		else
		{
			ActorRoot = NULL;
		}
	}
}

void Database::BinaryTree::DeleteFilmNode(TreeNode *Node)
{
	if (Node)
	{
		DeleteFilmNode(Node->Left);
		DeleteFilmNode(Node->Right);
		if (Node != FilmRoot) delete Node;
		else
		{
			FilmRoot = NULL;
		}
	}
}


//UI FUNCTIONS
void Database::ViewDatabase()
{
	cout << "View Database" << endl;
	cout << "\nHow do you want to sort the database?" << endl;
	createNewTree(PrintMenu({ "ID","Title","Revenue","Release Date","Status","Runtime" }));
	PrintFilmResults(PrintMenu({ "Ascending", "Descending" }));
}

void Database::SearchDatabase()
{
	char Order = '<'; string Query;
	cout << "What field do you want to search: " << endl;
	string Field = PrintMenu({ "Title","Genre","Production Companies","Languages","Locations","Revenue","Runtime","Released","Status"});
	if (Field == "6" || Field == "7" || Field == "8")
	{
		cout << "Search for greater than or less than?" << endl;
		if (PrintMenu({ "Greater Than", "Less Than" }) == "1") Order = '>';
	}
	cout << "What do you want to search for: " << endl;	
	getline(cin, Query);
	Search(Field, Query, Order,Tree.FilmResults,0);


}

void Database::FilmInfo()
{
	string ID; Film* film;
	cout << "Enter the ID of the film.";
	getline(cin, ID);
	if (!(film = Find(ID, &Storage)))
	{
		cout << "Sorry could not find that film." << endl;
	}
	else
	{
		cout << "Selected Film : " << film->Title << endl;
		cout << "What would you like to view?" << endl;
		string Choice;
		while ((Choice = PrintMenu({ "Film Overview","Cast Overview","Crew Overview","Material Overview","Return" })) != "5")
		{
			if (Choice == "1") film->Overview();
			else if (Choice == "2") PrintFilmActors(film->CastIDs, film->ID);
			else if (Choice == "3") film->PrintCrewInfo();
			else if (Choice == "4")film->PrintMaterialInfo();
		}
	}
}

void Database::AddFilm()
{
	if (!LoggedIn)
	{
		cout << "You must be logged in to add films" << endl;
	}
	else {
		cout << "Film status" << endl;
		int LocalStatus;
		LocalStatus = (stoi(PrintMenu({ "Released", "Now-Playing","Unreleased" })) - 1);

		string input; int IntInput;
		GenerateID();
		string FilmLine = NEXT_ID + "|";
		cout << "\nTitle: " << endl;
		FilmLine += GetStrInput() + "|";

		cout << "\nFilm Genres: " << endl;
		FilmLine += VectorAsString(GetVectorInputs()) + "|";

		cout << "\nSummary: " << endl;
		FilmLine += GetStrInput() + "|";

		cout << "\nProduction Companies: " << endl;
		FilmLine += VectorAsString(GetVectorInputs()) + "|";

		cout << "\nFilming Locations: " << endl;
		FilmLine += VectorAsString(GetVectorInputs()) + "|";

		cout << "\nRelease Date (YYYYMMDD)" << endl;
		IntInput = GetIntInput();
		while (to_string(IntInput).length() != 8)
		{
			IntInput = GetIntInput();
		}
		FilmLine += to_string(IntInput) + "|";

		
		if (LocalStatus != 2)
		{
			cout << "\nRevenue: (/wk)" << endl;
			FilmLine += to_string(GetIntInput()) + "|";
		}
		else
		{
			FilmLine += "0|";
		}
		

		cout << "\nRuntime: (mins)" << endl;
		FilmLine += to_string(GetIntInput()) + "|";

		cout << "\nLanguages" << endl;
		FilmLine += VectorAsString(GetVectorInputs()) + "|";

		FilmLine += to_string(LocalStatus);

		Film Temp(FilmLine);

		vector<Film>::iterator Index = (Storage.begin() + InOrder(Temp, Storage));
		Storage.insert(Index, Temp);
	}
}

void Database::EditFilm()
{
	if (!LoggedIn)
	{
		cout << "You must be logged in to Edit films" << endl;
	}
	else {
		cout << "Enter ID of film to edit" << endl;
		string ID;  Film* Pointer;
		getline(cin, ID);
		if (!(Pointer = Find(ID, &Storage)))
		{
			cout << "Sorry, that film could not be found" << endl;
		}
		else
		{
			cout << "What would you like to edit?" << endl;
			string Choice;
			while ((Choice = PrintMenu({ "Title","Summary","Genres","Locations","Langauges","Runtime","Release Date","Revenue","Status","Material Information","Return" })) != "11")
			{
				if (Choice == "10")
				{
					if (Pointer->Status != 0)
					{
						cout << "Cannot enter material information for a unreleased film" << endl;
					}
					else
					{
						MaterialDetails(Pointer);
					}
				}
				else if (Choice == "8")
				{
					if (Pointer->Status == 3)
					{
						cout << "You cannot enter revenue information for a coming soon film." << endl;
					}
					else
					{
						cout << "Please enter the revenue: ($/wk)" << endl;
						Pointer->Revenue = GetIntInput();
					}
				}
				else 
				{
					if (Choice == "1") Pointer->Title = GetStrInput();
					else if (Choice == "2") Pointer->Summary = GetStrInput();
					else if (Choice == "3") Pointer->Genres = GetVectorInputs();
					else if (Choice == "4") Pointer->Locations = GetVectorInputs();
					else if (Choice == "5") Pointer->Runtime = GetIntInput();
					else if (Choice == "6")
					{
						int IntInput = GetIntInput();
						while (to_string(IntInput).length() != 8)
						{
							IntInput = GetIntInput();
						}
						Pointer->ReleaseDate = IntInput;
					}	
					else if (Choice == "7") Pointer->Revenue = GetIntInput();
					else if (Choice == "8")
					{
						int IntInput = GetIntInput();
						while (IntInput != 0 || IntInput != 1||IntInput != 2)
						{
							IntInput = GetIntInput();
						}
						Pointer->Status = IntInput;
					}
				}
			}
		}
	}
}

void Database::DeleteFilm()
{
	if (!LoggedIn)
	{
		cout << "You must be logged in to Delete films" << endl;
	}
	else {
		cout << "Enter ID of film to delete" << endl;
		string Input; Film* Pointer;
		getline(cin, Input);
		if (!(Pointer = Find(Input, &Storage)))
		{
			cout << "Sorry, that film could not be found" << endl;
		}
		else
		{
			cout << "Are you sure you want to delete " << Pointer->Title << " ?  Y/N" << endl;
			getline(cin, Input);
			if (Input == "Y")
			{
				cout << "Deleted : " << Pointer->Title << endl;
				for (vector<string>::iterator i = Pointer->CastIDs.begin(); i != Pointer->CastIDs.end(); i++)
				{
					if (Find(*i, &ActorStorage)->DeleteFilm(Pointer->ID))
					{
						ActorStorage.erase(ActorStorage.begin() + GetIndex(*i, ActorStorage));
					}
				}
				Storage.erase(Storage.begin() + GetIndex(Pointer->ID, Storage));
			}
			else
			{
				cout << "Cancelled Deletion." << endl;
			}
		}
	}

}

void Database::MaterialDetails(Film* film)
{

	cout << "Material Info" << endl;
	vector<string> CurrentMaterials;

	string Choice;
	while ((Choice = PrintMenu({ "Add Materials","Edit Materials","Delete Materials","Return" })) != "4")
	{
		if (Choice == "1")
		{
			string input;
			cout << "Format" << endl;
			int Format = (stoi(PrintMenu({ "VHS", "DVD","DS_DVD","Combo Box Set","Blu-Ray" })) - 1);
			string MaterialLine = to_string(Format) + "/" + to_string(Format) + film->ID + "/";

			cout << "\nTitle: " << endl;
			MaterialLine += GetStrInput() + "/";

			if (Format == 0) MaterialLine += "Mono/";
			else
			{
				cout << "\nAudio Formats: " << endl;
				MaterialLine += VectorAsString(GetVectorInputs()) + "/";
			}

			cout << "\nPrice: $$.cc" << endl;
			MaterialLine += GetStrInput() + "/";

			cout << "\nFrame Aspect	 W:H" << endl;
			MaterialLine += GetStrInput() + "/";

			cout << "\nAudio Languages: " << endl;
			if (Format == 0) MaterialLine += GetStrInput() + "/";
			else
			{
				MaterialLine += VectorAsString(GetVectorInputs()) + "/";
			}

			if (Format != 0)
			{
				cout << "\nSubtitle Languages: " << endl;
				MaterialLine += VectorAsString(GetVectorInputs()) + "/";
			}

			if (Format == 2)
			{
				cout << "\nSide One Info: " << endl;
				MaterialLine += GetStrInput();
				cout << "\nSide Two Info: " << endl;
				MaterialLine += GetStrInput();
			}
			
			film->Materials.push_back(Film::Material(MaterialLine));
		}
		else if (Choice == "2")
		{
			for (vector<Film::Material>::iterator i = film->Materials.begin(); i != film->Materials.end(); i++)
			{
				CurrentMaterials.push_back(i->ID);
			}

			cout << "What Material do you want to edit?" << endl;
			Film::Material* Pointer = &film->Materials[(stoi(PrintMenu(CurrentMaterials)) - 1)];
			cout << "What detail do you want to edit?" << endl;
			string ToChange;
			while ((ToChange = PrintMenu({ "Title","Audio Format","Price","Frame Aspect","Audio Languages","Subtitle Languages","Side One Info","Side Two Info","Return" })) != "9")
			{
				if (ToChange == "1") Pointer->Title = GetStrInput();
				else if (ToChange == "2")
				{
					if (Pointer->Format == 0) Pointer->AudioFormat = GetStrInput();
					else Pointer->AudioFormat = VectorAsString(GetVectorInputs());
				}
				else if (ToChange == "3") Pointer->Cost = GetStrInput();
				else if (ToChange == "4") Pointer->FA = GetStrInput();
				else if (ToChange == "5")
				{
					if (Pointer->Format == 0) Pointer->AudioLanguages = vector<string>({ GetStrInput() });
					else Pointer->AudioLanguages = GetVectorInputs();
				}
				else if (ToChange == "6")
				{
					if (Pointer->Format == 0)
					{
						cout << "VHS cannot have subtitles" << endl;
					}
					else
					{
						Pointer->SubtitleLanguages = GetVectorInputs();
					}
				}
				else if (ToChange == "7")
				{
					if (Pointer->Format != 2)
					{
						cout << "Only DS-DVD can have side info" << endl;
					}
					else
					{
						Pointer->SideOneInfo = GetStrInput();
					}
				}
				else if (ToChange == "8")
				{
					if (Pointer->Format != 2)
					{
						cout << "Only DS-DVD can have side info" << endl;
					}
					else
					{
						Pointer->SideTwoInfo = GetStrInput();
					}
				}
			}
		}
		else if (Choice == "3")
		{
			for (vector<Film::Material>::iterator i = film->Materials.begin(); i != film->Materials.end(); i++)
			{
				CurrentMaterials.push_back(i->ID);
			}

			cout << "What Material do you want to Delete?" << endl;
			int Index = stoi(PrintMenu(CurrentMaterials)) - 1;
			cout << "Are you sure you want to delete this Material?  Y/N" << endl;
			string Input; 
			getline(cin, Input);
			if (Input == "Y")
			{
				film->Materials.erase(film->Materials.begin() + Index);
			}
			else
			{
				cout << "Cancelled Deletion." << endl;
			}
		}
	}
}

void Database::LogIn()
{
	string usr, pw;
	cout << "Username : ";
	getline(cin, usr);
	cout << "Password : ";
	getline(cin, pw);

	if (usr == Username && pw == Password)
	{
		LoggedIn = true;
		cout << "Logged In." << endl;
	}
	else
	{
		cout << "Incorrect username or password." << endl;
	}
}

void Database::ViewActorDatabase()
{
	cout << "How would you like to sort?" << endl;
	cout << "\nHow do you want to sort the database?" << endl;
	createActorTree(PrintMenu({ "ID","Name","# Of Films"}));
	cout << "\nSorting... Please wait... \n" << endl;
	Tree.TraverseActors(PrintMenu({ "Ascending", "Descending" }));
	PrintActorVector();
}

void Database::SearchActorDatabase()
{
	cout << "What do you want to search by?" << endl;
	string Choice = PrintMenu({ "Name", "Number of Films" });
	string Input = GetStrInput();
	cout << "\nSearching... Please wait... \n" << endl;
	SearchActor(Input,Choice);
}

void Database::ActorOverview()
{
	string ID; Actor* Actor;
	cout << "Enter the ID of the Actor : ";
	getline(cin, ID);
	if (!(Actor = Find(ID, &ActorStorage)))
	{
		cout << "Sorry could not find that actor." << endl;
	}
	else
	{
		cout << "\n\nName : " << Actor->Name << endl;
		cout << "\nID : " << Actor->ID << endl;
		cout << "\nGender : " << GetGender(Actor->Gender) << endl;
		for (map<string, vector<string>>::iterator i = Actor->FilmRole.begin(); i != Actor->FilmRole.end(); i++)
		{
			cout << "\n\nFilm : " << GetFilmName(i->first) << "\nRole : " << VectorAsString(i->second) << endl;
		}
	}
}
