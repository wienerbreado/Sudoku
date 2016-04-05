#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Nonet.hpp"

using namespace std;

void fileReader(char filename[], Nonet* nonets[9]);

int eightyOneGet(int row, int col, Nonet* nonets[9]);

void eightyOneSet(int row, int col, Nonet* nonets[9], int value);

void printPuzzle(Nonet* nonets[9]);

void firstPass(Nonet* nonets[9]);

void removeChoicesInNonet(Nonet* nonet);



int main(int argc, char* argv[])
{
	int i = 0;
	Nonet* nonets[9];
	
	for (i = 0; i < 9; i++)
	{
		nonets[i] = new Nonet();
	}
	
	if (argc > 1)
	{
		fileReader(argv[1], nonets);
		firstPass(nonets);
		for (i = 0; i < 9; i++)
		{
			if (nonets[0]->getEntry(4)->isPossible(i))
			{
				cout << i + 1;
			}
		}
		cout << endl;
		printPuzzle(nonets);
	}
	else
	{
		cout << "No file specified." << endl;
	}
	
	return 0;
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

int eightyOneGet(int row, int col, Nonet* nonets[9])
{
	int non_r = row / 3;
	int non_r2 = row % 3;
	int non_c = col / 3;
	int non_c2 = col % 3;
	
	return(nonets[3 * non_r + non_c]->getEntry(3 * non_r2 + non_c2)->getValue());	
}

void eightyOneSet(int row, int col, Nonet* nonets[9], int value)
{
	int non_r = row / 3;
	int non_r2 = row % 3;
	int non_c = col / 3;
	int non_c2 = col % 3;
	
	nonets[3 * non_r + non_c]->insertEntry(3 * non_r2 + non_c2, value);	
}

void printPuzzle(Nonet* nonets[9])
{
	for (int i = 0; i < 81; i++)
	{
		if (i % 9 == 0)
		{
			cout << endl;
		}
		cout << eightyOneGet(i / 9, i % 9, nonets) << " ";
	}
}

void firstPass(Nonet* nonets[9])
{
	for (int i = 0; i < 9; i++)
	{
		removeChoicesInNonet(nonets[i]);
	}
}

void removeChoicesInNonet(Nonet* nonet)
{
	int x = 0;
	
	for (int i = 0; i < 9; i++)
	{
		if (nonet->getEntry(i)->getValue() == 0)
		{
			for (int j = 0; j < 9; j++)
			{
				x = nonet->getEntry(j)->getValue();
				if (x != 0)
				{
					nonet->getEntry(i)->changePossible(x - 1);
				}
			}
		}
	}
}