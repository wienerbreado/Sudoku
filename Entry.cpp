#include <iostream>
#include "Entry.hpp"

using namespace std;

Entry::Entry(int value)
{
	this->value = value;

	if (value == 0)
	{
		this->solved = false;
		for (int i = 0; i < 9; i++)
		{
			this->possible[i] = 1;
		}
	}
	else
	{
		this->solved = true;
	}
}

Entry::Entry(void) { }

void Entry::changePossible(int number)
{
	int x = 0, y = 0;
	
	if (!this->solved && number >= 0 && number < 9)
	{
		if (this->possible[number] != 0)
		{
			this->possible[number] = 0;
			
			for (int i = 0; i < 9; i++)
			{
				if (this->possible[i] == 1)
				{
					x++;
					y = i;
				}
			}
			
			if (x == 1)
			{
				this->solved = true;
				this->value = y + 1;
			}
		}
	}
	else
	{
		cout << "Unexpected condition in Entry::changePossible: " << number << endl;
	}
}

bool Entry::isPossible(int number)
{
	if (this->solved)
	{
		return false;
	}
	else if (number >= 0 && number < 9)
	{
		return this->possible[number] == 1;
	}
	else
	{
		cout << "Unexpected condition in Entry::isPossible: " << number << endl;
		return false;
	}
}

bool Entry::isSolved()
{
	return this->solved;
}

int Entry::getValue()
{
	return this->value;
}