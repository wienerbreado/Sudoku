#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Nonet.hpp"

using namespace std;

void fileReader(char filename[], Nonet* nonets[9]);

int eightyOneGet(int row, int col, Nonet* nonets[9]);

void eightyOneSet(int row, int col, Nonet* nonets[9], int value);



int main(int argc, char* argv[])
{
	cout << "Hello!" << endl;
}

void fileReader(char filename[], Nonet* nonets[9])
{
	int bleh = 0;

	try
	{
		ifstream puzzle(filename);
			
		if(puzzle.is_open())
		{
			for(int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					puzzle >> bleh;
					eightyOneSet(i, j, nonets, bleh);
				}
			}
		}
	}
	catch (...)
	{
		cout << "Whoops, error occurred in reading the file; A-Rod will get on it ASAP!" << endl;
		exit(30);
	}
}

/* void fillPossibleSpaces (Nonet nonet)
{
	for (int i = 0; i < 9; i++)
	{
		
	}
} */

int eightyOneGet(int row, int col, Nonet* nonets[9])
{
	int non_r = row / 3;
	int non_c = col / 3;
	int non_c2 = col % 3;
	
	return(nonets[3 * non_r + non_c]->getEntry(non_r, non_c2)->getValue());	
}

void eightyOneSet(int row, int col, Nonet* nonets[9], int value)
{
	int non_r = row / 3;
	int non_c = col / 3;
	int non_c2 = col % 3;
	
	nonets[3 * non_r + non_c]->insertEntry(non_r, non_c2, value);	
}