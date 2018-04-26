# include "Database.h"


template <class T>
T* Find(string ID, vector<T> *Vec)
{
	while (ID.length() < 6)
	{
		ID = "0" + ID;
	}

	int start = 0, end = Vec->size() - 1;
	while (start <= end)
	{
		int M = floor(((end + start) / 2));

		//cout << M;
		//cout << Vec->at(M).ID;

		if (Vec->at(M).ID == ID)
		{
			return &Vec->at(M);
		}
		if (Vec->at(M).ID < ID)
		{
			start = M + 1;
		}
		else
		{
			end = M - 1;
		}
	}
	return NULL;
}

template <class T>
int InOrder(T Value, vector<T> Vec)
{

	int start = 0, end = Vec.size() - 1;
	int M = 0;
	while (start <= end)
	{
		M = floor(((end + start) / 2));

		if (Vec[M].ID < Value.ID)
		{
			start = M + 1;
		}
		else if (Vec[M].ID > Value.ID)
		{
			end = M - 1;
		}
		else
		{
			break;
		}
	}

	if (Vec.size() != 0)	if (Value.ID > Vec[M].ID) M = M + 1;

	return M;
}


template <class T>
void SearchasdasActor(T Find,string Type)
{
	for (vector<Actor>::iterator i = ActorStorage.begin(); i != ActorStorage.end(); i++)
	{
		if (Type == "NAME")
		{
			if (ToLower(i->Name).find(ToLower(Find)) != string::npos)
			{
				ActorResults.push_back(&*i);
			}
		}
		else
		{
			if (to_string(i->FilmRole.size()) >= No)
			{
				ActorResults.push_back(&*i);
			}
		}
	}

	PrintActorVector();

	cout << "\n\nHere are the search results for: " << Find << endl;
}