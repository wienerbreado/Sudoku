#include <iostream>
#include "Nonet.hpp"

using namespace std;

Nonet::Nonet(void)
{
	this->solved = false;
}

void Nonet::insertEntry(int nonet_row, int nonet_col, int value)
{
	if (nonet_row >= 0 && nonet_row < 3 && nonet_col >= 0 && nonet_col < 3)
	{
		this->entries[nonet_row][nonet_col] = new Entry(value);
	}
	else 
	{
		if (nonet_row < 0 || nonet_row > 2)
		{
			cout << "Unexpected condition in Nonet::insertEntry: row = " << nonet_row << endl;
		}
		if (nonet_col < 0 || nonet_col > 2)
		{
			cout << "Unexpected condition in Nonet::insertEntry: col = " << nonet_col << endl;
		}
	}
}

Entry* Nonet::getEntry(int nonet_row, int nonet_col)
{
	if (nonet_row >= 0 && nonet_row < 3 && nonet_col >= 0 && nonet_col < 3)
	{
		return this->entries[nonet_row][nonet_col];
	}
	else 
	{
		if (nonet_row < 0 || nonet_row > 2)
		{
			cout << "Unexpected condition in Nonet::getEntry: row = " << nonet_row << endl;
		}
		if (nonet_col < 0 || nonet_col > 2)
		{
			cout << "Unexpected condition in Nonet::getEntry: col = " << nonet_col << endl;
		}
		
		return NULL;
	}
}

bool Nonet::isSolved()
{	
	for (int i = 0; i < 9; i++)
	{
		if (this->entries[i / 3][i % 3]->getValue() == 0)
		{
			return false;
		}
	}
	
	return true;
}
