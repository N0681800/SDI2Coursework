#include "Database.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <vector>
#include <map>
#include <sstream>

#include "Library.h"

Database::Database(string filmPath_, string ccPath_, int Max)
{
	filmPath = filmPath_;
	ccPath = ccPath_;
	FilmSetup(Max);
	//CastCrewSetup(Max);
	createNewTree("ID");
}

Database::~Database()
{
	SaveData();
}

void Database::FilmSetup(int MAX)
{
	string Line;
	ifstream FromFile(filmPath);
	if (FromFile.is_open()) cout << "\nFile sucessfully Loaded!\n" << endl;

	while (getline(FromFile, Line))
	{
		Film Film(Line); Film.Setup();

		Storage.push_back(Film);

		if (Storage.size() == MAX) break;
	}

	cout << "\n"<< Storage.size() << " Films Loaded.\n" << endl;

}

/*
bool Database::ccExists(string ID, bool isCast)
{
	bool exists = false;
	for (vector<CastCrew>::const_iterator i = ccStorage.begin(); i != ccStorage.end(); i++)
	{
		CastCrew Temp = *i;
		if ((Temp.ID == ID) && (Temp.isCast = isCast)) { exists = true; break; }
	}
	return exists;
}
*/

void Database::PrintResults(string Order)//Prints out details of a number of films
{
	const int MaxTitleLength = 35;
	const int MaxGenreLength = 20;
	char Border = 179;

	cout << setw(MaxTitleLength + 3) << left << "Title" << Border;
	cout << setw(MaxGenreLength + 6) << left << "Genres" << Border;
	cout << setw(10) << left << "Released" << Border;
	cout << setw(10) << left << "Runtime" << Border;
	cout << setw(18) << left << "Box Office Sales" << Border;
	cout << setw(12) << left << "Status" << Border << endl;

	PrintTable();

	CURRENT_SORT_TYPE = Order;
	Tree.printTree(Order);


}


void Database::Search(string SearchField, string Query)//Searchs field for a value
{
	Tree.Delete();
	createNewTree(SearchField);
	cout << Tree.getSize()<<endl;

	Tree.SearchFilm(SearchField, Query);
	cout << Tree.Films.size();
	
	/*
	for (vector<Film>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Film Result = *i;

		SearchFields["ID"] = (Result.ID); SearchFields["Title"] = (Result.Title); SearchFields["Status"] = Result.Status;
		SearchFields["Genres"] = VectorAsString(Result.Genres); SearchFields["ProdComps"] = VectorAsString(Result.ProdComps);
		SearchFields["Locations"] = VectorAsString(Result.Locations); SearchFields["Languages"] = VectorAsString(Result.Languages);

		SearchFields["Revenue"] = Result.Revenue; //Special case
		SearchFields["Date"] = Result.ReleaseDate; //Special case
		SearchFields["Runtime"] = Result.Runtime; //Special case



		if ((ToLower((SearchFields.find(SearchField)->second))).find(ToLower(Query)) != string::npos)
		{
			Temp.push_back(Result);
		}
	}
	cout << "Here are the search results for: " << Query << "in" << SearchField << endl;
	PrintResults(Temp);

	return Temp;
	*/
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

bool Database::SaveData()
{
	bool Saved = false;
	
	ofstream outFile;// ("new.txt");
	outFile.open("Database.txt", ios::in);

	for (vector<Film>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		outFile << i->ID + "|" + i->Title + "|" + VectorAsString(i->Genres) + "|" + i->Summary + "|" + VectorAsString(i->ProdComps) + "|" + VectorAsString(i->Locations) + "|" + i->ReleaseDate + "|" + to_string(i->Revenue) + "|" + to_string(i->Runtime) + "|" + VectorAsString(i->Languages) + "|" + to_string(i->Status) << endl;
	}
	outFile.flush();
	Saved = true;
	outFile.close();
	return Saved;
}

void Database::createNewTree(string SortBy)
{
	for (std::vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
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
		if (toSort == "REVENUE" || toSort == "RUNTIME" || toSort == "STATUS")
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
	Comparison["REVENUE"] = { &toAdd->Revenue,&Node->FilmInfo->Revenue };
	Comparison["RUNTIME"] = { &toAdd->Runtime,&Node->FilmInfo->Runtime };
	Comparison["STATUS"] = { &toAdd->Status,&Node->FilmInfo->Status };

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
	Comparison["ID"] = { &toAdd->ID,&Node->FilmInfo->ID };
	Comparison["TITLE"] = { &toAdd->Title,&Node->FilmInfo->Title };
	Comparison["RELEASEDATE"] = { &toAdd->ReleaseDate,&Node->FilmInfo->ReleaseDate };


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


void Database::BinaryTree::SearchFilm(string toSearch, string Find)
{
	SearchTree(Root, toSearch, Find);
}

void Database::BinaryTree::SearchTree(TreeNode* Node, string toSearch, string toFind)
{

	map<string,string*> Search;
	Search["ID"] = { &Node->FilmInfo->ID };
	Search["TITLE"] = { &Node->FilmInfo->Title };
	//Search["GENRE"] = { &Node->FilmInfo->Genres };
	//Search["PRODCOMP"] = { &Node->FilmInfo->ProdComps };
	//Search["LANGUAGES"] = { &Node->FilmInfo->Languages };
	//Search["STATUS"] = { &Node->FilmInfo->Status };

	Search["RELEASED"] = { &Node->FilmInfo->ReleaseDate };
	//Search["REVENUE"] = { &Node->FilmInfo->Revenue };
	//Search["RUNTIME"] = { &Node->FilmInfo->Runtime };


	if (ToLower(*Search[toSearch]).find(ToLower(toFind)) != string::npos)
	{
		Films.push_back(Node->FilmInfo);
	}


	if ((ToLower(*Search[toSearch]) >= ToLower(toFind)))
	{
		if (Node->Left)
		{
			SearchTree(Node->Left, toSearch, toFind);
		}
	}
	else
	{
		if (Node->Right)
		{
			SearchTree(Node->Right, toSearch, toFind);
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
	if (Order == "ASC")
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




/*
void Database::CastCrewSetup(int MAX)
{
	string Line;
	ifstream CastFile(ccPath);
	getline(CastFile, Line);
	cout << Line << endl;

	string TokenizedData, TempData[3]; int i = 0;
	stringstream LineOfData(Line);
	while (getline(LineOfData, TokenizedData, '|')) //getting data
	{
		cout << TokenizedData << endl;
		TempData[i] = TokenizedData; //Store data in temp array
		i++;
	}

	bool isCast = true;
	stringstream Actors(TempData[1]); string Actor, ActorInfo[5];
	while (getline(Actors, Actor, '/')) //getting data
	{
		stringstream ActorInfoStream(Actor);
		int j = 0;
		while (getline(ActorInfoStream, ActorInfo[j], '\,'))
		{
			cout << ActorInfo[j] << endl;
			j++;
		}
		//Check info
		if (!ccExists(ActorInfo[2], isCast)) CastCrew Temp(ActorInfo[2], ActorInfo[3], GetGender(ActorInfo[1]), isCast);


	}

	//role,gender,id,name
}

string Database::GetFilmTitle(string FilmID)
{
	string Title;
	for (vector<Film>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Film Temp = *i;
		if (Temp.ID == FilmID)
		{
			Title = Temp.Title; break;
		}
	}

	return Title;
}
*/