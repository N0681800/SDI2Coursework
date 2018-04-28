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
	createNewTree("2");
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
	for (int i = 0; i < MAX; i ++)
	{ 
		getline(MaterialFile, Line);
	
		vector<string> MaterialLine = AddTokens(Line, '|');
		
		try {
			Film* Pointer;
			if (!(Pointer = (Find(MaterialLine[0], &Storage))))
			{
				throw(50);
			}
			else
			{
				for (vector<string>::iterator i = MaterialLine.begin() + 1; i != MaterialLine.end(); i++)
				{
					Pointer->Materials.push_back(Film::Material(*i));
					n++;
				}
			}
		}
		catch (int a) 
		{
			continue;//Film does not exist skip over it
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
		getline(CastCrewFile, Line);
	
		vector<string> CastCrewLine = AddTokens(Line, '|');

		while (CastCrewLine[0].length() < 6)
		{
			CastCrewLine[0] = "0" + CastCrewLine[0];
		}

		try {
			Film* Pointer;
			if (!(Pointer = (Find(CastCrewLine[0], &Storage))))
			{
				throw(50);
			}
			else
			{
				CrewN += Pointer->AddCrew(CastCrewLine[2]);
				Pointer->CastIDs = AddActors(CastCrewLine[0],CastCrewLine[1]);
			}
		}
		catch (int a)

		{
			continue;//Film does not exist skip over it
		}
	}
	cout << "\n" << ActorStorage.size() << " Actors loaded.\n" << endl;
	cout << "\n" << CrewN << " Crew members loaded.\n" << endl;
}

void Database::PrintResults(string Order)//Prints out details of a number of films
{
	PrintTableHeader(FILM_TABLE);
	CURRENT_SORT_TYPE = Order;
	Tree.printTree(Order);
}

void Database::Search(string SearchField, string Query,char Order)//Searchs field for a value
{
	
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
				Results.push_back(&*i);
			}
		}
		
		if (Results.size() > 0)
		{
			PrintResultsVector();
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
					Results.push_back(&*i);
				}
			}
			else
			{
				if (SearchFields[SearchField] <= stoi(Query))
				{
					Results.push_back(&*i);
				}
			}
		}
		
		if (Results.size() > 0)
		{
			PrintResultsVector();
		}
	}
	else //Sort by status
	{
		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{
			if (i->Status == stoi(Query))
			{
				Results.push_back(&*i);
			}
		}
		if (Results.size() > 0)
		{
			PrintResultsVector();
		}
	}
}

void Database::SearchActorName(string Find)
{
	for (vector<Actor>::iterator i = ActorStorage.begin(); i != ActorStorage.end(); i++)
	{

		if (ToLower(i->Name).find(ToLower(Find)) != string::npos)
		{
			ActorResults.push_back(&*i);
		}
	}

	PrintActorVector();

	cout << "\n\nHere are the search results for: " << Find << endl;
}

void Database::SearchActor(string Value,string Type)
{
	for (vector<Actor>::iterator i = ActorStorage.begin(); i != ActorStorage.end(); i++)
	{
		if (to_string(i->FilmRole.size()) >= Value)
		{
			ActorResults.push_back(&*i);
		}
	}


	PrintActorVector();

	cout << "\n\nHere are the search results for actors with more than: " << Value << " films" << endl;

}

void Database::PrintResultsVector()
{
	PrintTableHeader(FILM_TABLE);

	for (vector<Film*>::iterator i = Results.begin(); i != Results.end(); i++)
	{
		(*i)->Details();
	}
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

void Database::PrintActorVector()
{
	PrintTableHeader(ACTOR_TABLE);
	for (vector<Actor*>::iterator i = ActorResults.begin(); i != ActorResults.end(); i++)
	{
		(*i)->Details();
		
		cout << setw(MAX_FILM_LENGTH) << left << SetLength(VectorAsString(GetFilms((*i)->ID)), MAX_FILM_LENGTH) << BORDER<<endl;

		PrintTable(ACTOR_TABLE);
	}
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
				throw 50;
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
		catch (int a)
		{
			//Not enough info exception
		}
	}
	return ActorIDs;
}

string Database::GenerateID()
{
	string ID, Line, CurrentID;
	ifstream File; File.open("Database.txt");

	bool IDFound = false;
	int i = 2;
	while (!IDFound)
	{
		ID = to_string(i);
		while (ID.length() < 6) { ID = "0" + ID; }

		getline(File, Line); stringstream IDToken(Line); getline(IDToken, CurrentID, '|');

		if (CurrentID == ID) i++;

		else IDFound = true;
	}
	return ID;
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
	
	ofstream outFile(filmPath);
	ofstream MaterialoutFile(matPath);
	ofstream CastCrewoutFile(ccPath);

	for (vector<Film>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Film Temp = *i; 
		outFile << Temp.Save() << endl;
		MaterialoutFile << Temp.SaveMaterials() << endl;
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
	Tree.Delete();
	for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		CURRENT_SORT = SortBy;
		//CURRENT_SORT_TYPE
		Tree.Insert(&*i, SortBy);
	}
}

Database::BinaryTree::BinaryTree()
{
Root = NULL;
}

void Database::BinaryTree::Insert(Film *toAdd, string toSort)
{
	if (!Root)
	{
		Root = new TreeNode;
		Root->Left = NULL;
		Root->Right = NULL;
		Root->FilmInfo = toAdd;
	}
	else
	{
		if (toSort == "REVENUE" || toSort == "RUNTIME" || toSort == "STATUS" || toSort == "RELEASEDATE")
		{
			insertInt(Root, toAdd, toSort);
		}
		else
		{
			insertString(Root, toAdd, toSort);
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

void Database::BinaryTree::printTree(string Order)
{
	Print(Root,Order);
}

void Database::BinaryTree::Print(TreeNode *Node,string Order)
{
	if (!Node)
	{
		return;
	}
	if (Order == "1")
	{ 
		Print(Node->Left,Order);
		Node->FilmInfo->Details();
		Print(Node->Right,Order);
	}
	else 
	{
		Print(Node->Right, Order);
		Node->FilmInfo->Details();
		Print(Node->Left, Order);
	}
}

int Database::BinaryTree::getSize()
{
	return Size(Root);
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



void Database::BinaryTree::Delete()
{
	DeleteNode(Root);
}

void Database::BinaryTree::DeleteNode(TreeNode *Node)
{
	if (Node)
	{
		DeleteNode(Node->Left);
		DeleteNode(Node->Right);
		if (Node != Root) delete Node;
		else
		{
			Root = NULL;

		}
	}
}

//UI FUNCTIONS
void Database::ViewDatabase()
{
	cout << "View Database" << endl;
	cout << "\nHow do you want to sort the database?" << endl;
	createNewTree(PrintMenu({ "ID","Title","Revenue","Release Date","Status","Runtime" }));
	PrintResults(PrintMenu({ "Ascending", "Descending" }));
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
	cin >> Query;
	Search(Field, Query, Order);
}

void Database::FilmInfo()
{
	string ID; Film* film;
	cout << "Enter the ID of the film.";
	cin >> ID;
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
		FilmLine += IntInput + "|";

		/*
		if (LocalStatus == 2)
		{
			cout << "\nRevenue: (/wk)" << endl;
			FilmLine += GetIntInput() + "|";
		}
		else
		{
			FilmLine += "0|";
		}
		*/
		cout << "\nRuntime: (mins)" << endl;
		FilmLine += GetIntInput() + "|";

		cout << "\nLanguages" << endl;
		FilmLine += VectorAsString(GetVectorInputs()) + "|";

		FilmLine += LocalStatus;

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
	}
}

void Database::DeleteFilm()
{
	if (!LoggedIn)
	{
		cout << "You must be logged in to Delete films" << endl;
	}
	else {
	}

}

void Database::LogIn()
{
	string usr, pw;
	cout << "Username : ";
	cin >> usr;
	cout << "Password : ";
	cin >> pw;

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