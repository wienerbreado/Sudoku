#include <iostream>
#include "Nonet.hpp"

using namespace std;

Nonet::Nonet(void)
{
	this->solved = false;
}

void Nonet::insertEntry(int place, int value)
{
	if (place >= 0 && place < 9)
	{
		this->entries[place] = new Entry(value);
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
	for (int i = 0; i < 9; i++)
	{
		if (this->entries[i]->getValue() == 0)
		{
			return false;
		}
	}
	
	return true;
}
