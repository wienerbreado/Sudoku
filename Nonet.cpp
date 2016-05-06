#include <iostream>
#include "Nonet.hpp"

using namespace std;

Nonet::Nonet(void)
{
	for (int i = 0; i < 9; i++)
	{
		this->entries[i] = NULL;
	}
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


void Nonet::checkForLonersAndSolveThemIfTheyExist()
{
	int counter, placeholder, number;
	
	for (int i = 0; i < 9; i++)
	{
		counter = 0;
		for (int j = 0; j < 9; j++)
		{
			if(this->entries[j]->isPossible(i))
			{
				counter++;
				if (counter > 1)
				{
					j = 10;
				}
				placeholder = j;
				number = i;
			}
		}
		
		if (counter == 1)
		{
			this->entries[placeholder] = new Entry(number);
		}
	}
}


void Nonet::removeChoices()
{
	Entry *y;
	int x = 0;
	
	for (int i = 0; i < 9; i++)
	{
		y = this->getEntry(i);
		
		for (int j = 0; j < 9 && !y->isSolved(); j++)
		{
			x = this->getEntry(j)->getValue();
			if (x != 0)
			{
				this->getEntry(i)->changePossible(x - 1);
			}
		}
	}
}

	
bool Nonet::isSolved()
{	
	for (int i = 0; i < 9; i++)
	{
		if (!this->entries[i]->isSolved())
		{
			return false;
		}
	}

	return true;
}