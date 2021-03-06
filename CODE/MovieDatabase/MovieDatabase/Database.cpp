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
	//CastCrewSetup(Max);
	createNewTree("TITLE");
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
	while(getline(MaterialFile, Line))
	{
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

void Database::PrintResults(string Order)//Prints out details of a number of films
{
	const int MaxTitleLength = 35;
	const int MaxGenreLength = 20;
	const int MaxMaterialLength = 15;
	char Border = 179;

	cout << setw(6) << left << "ID" << Border;
	cout << setw(MaxTitleLength + 3) << left << "Title" << Border;
	cout << setw(MaxGenreLength + 6) << left << "Genres" << Border;
	cout << setw(10) << left << "Released" << Border;
	cout << setw(10) << left << "Runtime" << Border;
	cout << setw(18) << left << "Box Office Sales" << Border;
	cout << setw(12) << left << "Status" << Border;
	cout << setw(MaxMaterialLength + 3) << left << "Avalible Materials" << Border << endl;

	PrintTable();

	CURRENT_SORT_TYPE = Order;
	Tree.printTree(Order);
}

void Database::Search(string SearchField, string Query,char Order)//Searchs field for a value
{

	if (SearchField == "TITLE" || SearchField == "GENRE" || SearchField == "PRODCOMP" || SearchField == "LANGUAGES" || SearchField == "LOCATIONS")
	{
		map<string, string> SearchFields;

		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{

			SearchFields["TITLE"] = i->Title;
			SearchFields["GENRE"] = VectorAsString(i->Genres); SearchFields["PRODCOMP"] = VectorAsString(i->ProdComps);
			SearchFields["LOCATIONS"] = VectorAsString(i->Locations); SearchFields["LANGUAGES"] = VectorAsString(i->Languages);

			if ((ToLower(SearchFields[SearchField])).find(ToLower(Query)) != string::npos)
			{
				Results.push_back(&*i);
			}
		}
		

		PrintResultsVector();

		cout << "\n\nHere are the search results for: " << Query << "in" << SearchField << endl;
	}
	
	else if (SearchField == "REVENUE" || SearchField == "RUNTIME" || SearchField == "RELEASED")
	{
		map<string, int> SearchFields;
		for (vector<Film>::iterator i = Storage.begin(); i != Storage.end(); i++)
		{
			 
			SearchFields["REVENUE"] = i->Revenue; SearchFields["RUNTIME"] = i->Runtime; SearchFields["RELEASED"] = i->ReleaseDate;
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
		

		PrintResultsVector();

		cout << "\n\nHere are the search results for: " << SearchField << " " << Order << " " << Query << endl;

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

		PrintResultsVector();

		if  (Query == "0") cout << "\n\nHere are the search results for status: Released"<< endl;
		else if (Query == "1")	cout << "\n\nHere are the search results for status: Now Playing" << endl;
		else cout << "\n\nHere are the search results for status: Unreleased" << endl;

		
	}

	
}

void Database::PrintResultsVector()
{
	const int MaxTitleLength = 35;
	const int MaxGenreLength = 20;
	const int MaxMaterialLength = 15;
	char Border = 179;

	cout << setw(6) << left << "ID" << Border;
	cout << setw(MaxTitleLength + 3) << left << "Title" << Border;
	cout << setw(MaxGenreLength + 6) << left << "Genres" << Border;
	cout << setw(10) << left << "Released" << Border;
	cout << setw(10) << left << "Runtime" << Border;
	cout << setw(18) << left << "Box Office Sales" << Border;
	cout << setw(12) << left << "Status" << Border;
	cout << setw(MaxMaterialLength + 3) << left << "Avalible Materials" << Border << endl;

	PrintTable();

	for (vector<Film*>::iterator i = Results.begin(); i != Results.end(); i++)
	{
		(*i)->Details();
	}
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
	
	ofstream outFile("Database.txt");
	ofstream MaterialoutFile("Materials.txt");

	for (vector<Film>::const_iterator i = Storage.begin(); i != Storage.end(); i++)
	{
		Film Temp = *i; 
		outFile << Temp.Save() << endl;
		MaterialoutFile << Temp.SaveMaterials() << endl;;
	}

	outFile.flush();
	MaterialoutFile.flush();
	
	Saved = true;

	MaterialoutFile.close();
	outFile.close();
	return Saved;
}

void Database::createNewTree(string SortBy)
{
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
	Comparison["REVENUE"] = { &toAdd->Revenue,&Node->FilmInfo->Revenue };
	Comparison["RUNTIME"] = { &toAdd->Runtime,&Node->FilmInfo->Runtime };
	Comparison["STATUS"] = { &toAdd->Status,&Node->FilmInfo->Status };
	Comparison["RELEASEDATE"] = { &toAdd->ReleaseDate,&Node->FilmInfo->ReleaseDate };

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

/*
void Database::BinaryTree::SearchFilm(string toSearch, string Find)
{
	//SearchTree(Root, toSearch, Find);
}


void Database::BinaryTree::SearchTree(TreeNode* Node, string toSearch, int toFind, char Parameter)
{

	if (!Node)
	{
		return;
	}
	if (Parameter == '<')//LEss than
	{
		if (toFind < Node->FilmInfo->Revenue)
		{
			//add to results
			SearchTree(Node->Left, toSearch, toFind, Parameter);
		}

	}
	else //Greater than
	{





	}

	//Search["ID"] = { &Node->FilmInfo->ID };
	//Search["TITLE"] = { &Node->FilmInfo->Title };
	//Search["GENRE"] = { &Node->FilmInfo->Genres };
	//Search["PRODCOMP"] = { &Node->FilmInfo->ProdComps };
	//Search["LANGUAGES"] = { &Node->FilmInfo->Languages };
	//Search["STATUS"] = { &Node->FilmInfo->Status };

	//string hello = (Node->FilmInfo->ReleaseDate);
	//int hi = stoi(Node->FilmInfo->ReleaseDate);
	//int* hey = &int(stoi(Node->FilmInfo->ReleaseDate));


	//Search["RELEASED"] = { stoi(Node->FilmInfo->ReleaseDate) };
	struct intPtr
	{
		int* value;
		int* Left;
		int* Right;
	};

	map<string, intPtr*> Search;
	Film Tempy = **&Node->FilmInfo;

	intPtr Rev;
	Rev.value = &Node->FilmInfo->Revenue;
	Rev.Left = &Node->Left->FilmInfo->Revenue;
	Search["REVENUE"] = { &Node->FilmInfo->Revenue,&Node->Left->FilmInfo->Revenue,&Node->Right->FilmInfo->Revenue };
	Search["RUNTIME"] = { &Node->FilmInfo->Runtime };

	//Search["REVENUE"] = { &Tempy.Revenue };
	//Search["RUNTIME"] = { &Tempy.Runtime };

	if (Search[toSearch] > &toFind)
	{
		Results.push_back((Node->FilmInfo));
	}



	if (Search[toSearch] >= toFind))
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
*/

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