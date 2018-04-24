# include "Database.h"


template <class T>
T* Database::Find(string ID, vector<T> *Vec)
{
	while (ID.length() < 6)
	{
		ID = "0" + ID;
	}

	int start = 0, end = Vec->size() - 1;
	while (start <= end)
	{
		int M = floor(((end - start) / 2));

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