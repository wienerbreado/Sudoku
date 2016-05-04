#include <iostream>
#include "Nonet.hpp"

using namespace std;

Nonet::Nonet(void)
{
	this->solved = false;
	for (int i = 0; i < 9; i++)
	{
		this->entries[i] = NULL;
	}
}

void Nonet::insertEntry(int place, int value)
{
	int i = 0;
	bool check = true;

	if (!this->solved && place >= 0 && place < 9)
	{
		this->entries[place] = new Entry(value);

		while (check && i < 9)
		{
			if (this->entries[i] == NULL)
			{
				check = false;
			}
			else
			{
				check = this->entries[i]->isSolved();
				i++;
			}
		}

		this->solved = (i == 9);
	}
	else 
	{
		cout << "Unexpected condition in Nonet::insertEntry: place = " << place << endl;
	}
}

Entry* Nonet::getEntry(int place)
{
	if (place >= 0 && place < 9)
	{
		return this->entries[place];
	}
	else 
	{
		cout << "Unexpected condition in Nonet::getEntry: place = " << place << endl;
		return NULL;
	}
}

bool Nonet::isSolved()
{	
	return this->solved;
}
