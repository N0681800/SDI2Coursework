#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;






class TwoTypes
{
public:

	int b;
	string a;

	void PrintDetails()
	{
		cout << "a: " << a << "b: " << b << endl;
	}
};


auto Hello(int a)
{

	return a;
}


class BinaryTree
{
public:
	vector <TwoTypes*> Results;

	BinaryTree()
	{
		Root = NULL;
	}
	/*
	void Insert(TwoTypes *Value, string toCompare)
	{
		if (!Root)
		{
			Root = new TreeNode;
			Root->Left = NULL;
			Root->Right = NULL;
			Root->Number = Value;
		}
		else
		{
			insertValue(Root, Value, toCompare);
		}
	}

	void printTree()
	{
		Print(Root);
	}
	
	void Search(string toSearch,string Find)
	{
	SearchTree(Root,toSearch, Find);
	}
	*/
	int getSize()
	{
		return Size(Root);
	}

	void Delete()
	{
		DeleteNode(Root);
	}

private:

	struct TreeNode
	{
		TwoTypes *Number;
		TreeNode *Left;
		TreeNode *Right;
	};



	TreeNode * Root; // = new TreeNode;
					 /*
					 void SearchTree(TreeNode* Node,string toSearch,string toFind)
					 {
					 struct Ptr
					 {
					 string *Value;
					 string *Node;
					 };
					 map<string, Ptr> Search;
					 Search["a"] = {&Node->Number->a};
					 Search["b"] = {&Node->Number->b};

					 //ToLower((SearchFields.find(SearchField)->second))).find(ToLower(Query)) != string::npos

					 if (ToLower(*Search[toSearch].Value).find(ToLower(toFind)) != string::npos)
					 {
					 Results.push_back(Node->Number);
					 }


					 if ((ToLower(*Search[toSearch].Value) > ToLower(toFind)))
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
					 
	void insertValue(TreeNode *Node, TwoTypes *Values, string toCompare)
	{
		template <class T>
		struct Ptr {
			T NodePtr;
			T ValuePtr;
		public:
			GetNode(*Node, Values, toCompare)
			{
				if (toCompare == "a")
				{
					NodePtr = &Node->Number->a;
				}
				else
				{
					NodePtr = &Node->Number->b;
				}
			}

			GetValue(*Node, Values, toCompare)
			{
				if (toCompare == "a")
				{
					ValuePtr = &Values->a;
				}
				else
				{
					ValuePtr = &Values->b;
				}
			}
		};

		Ptr<string> NodePtr = GetNode(*Node, Values, toCompare);
		template <class T>
		ValuePtr<string> = GetValue(Node, Values, toCompare);

		//auto Ptr = strComparison[toCompare];

		if (ValuePtr < NodePtr)
		{
			if (!(Node->Left))
			{
				Node->Left = new TreeNode;
				Node->Left->Left = NULL;
				Node->Left->Right = NULL;
				Node->Left->Number = Values;
			}
			else
			{
				insertValue(Node->Left, Values, toCompare);
			}
		}
		else if (ToLower(*Ptr.Value) > ToLower(*Ptr.Node))
		{
			if (!(Node->Right))
			{
				Node->Right = new TreeNode;
				Node->Right->Left = NULL;
				Node->Right->Right = NULL;
				Node->Right->Number = Values;
			}
			else
			{
				insertValue(Node->Right, Values, toCompare);
			}
		}
		else //Numbers same
		{
			if (!(Node->Right))
			{
				Node->Right = new TreeNode;
				Node->Right->Left = NULL;
				Node->Right->Right = NULL;
				Node->Right->Number = Values;
			}
			else
			{
				insertValue(Node->Right, Values, toCompare);
			}
		}
	}

	*/
	void Print(TreeNode *Node)
	{
		if (!Node)
		{
			return;
		}
		Print(Node->Left);
		Node->Number->PrintDetails();
		Print(Node->Right);
	}

	void DeleteNode(TreeNode *Node)
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

	int Size(TreeNode* Node)
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
};


vector<TwoTypes> Numbers = { { 1,"one" } ,{ 10, "Hello" },{ 69, "tits" } };

template <typename T> void Display(T x, T y)
{
	cout << "x: " << x << "y: " << y << endl;
}

template <typename K>
struct Hi
{
	K Name;
	K Time;
};


int main()
{
	template <typename K>
	map<string, Hi<K>> Yolo;
	template <typename K>
	Yolo["a"] = { 5,6 };
	template <typename K>
	Yolo["b"] = { "yo","dude" };
	


	//Database Database("CompleteDatabase.txt","CastCrew.txt.",100);

	//BinaryTree BT;
	//for (vector<TwoTypes>::iterator i = Numbers.begin(); i != Numbers.end(); i++)
	//{
	//	BT.Insert(&*i, "a");
	//}

	//BT.printTree();


	//getchar();

	cout << "hello" << endl;


	Display("Hi", "Goodbye");
	Display(1, 2);



	getchar();
	getchar();

	return 0;
}

