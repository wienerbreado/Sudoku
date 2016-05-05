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

Entry* decodeEntry(int row, int col, Nonet* nonets[9]);

void alanPalomo(Nonet* nonets[9]);

bool isSolved(Nonet *nonets[9]);

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
		printPuzzle(nonets);
		/////////////////////////////////
		/*
		for (i = 0; i < 9; i++)
		{
			if (nonets[0]->getEntry(4)->isPossible(i))
			{
				cout << i + 1;
			}
		}
		cout << endl;
		*///////////////////////////////
		i = 0;
		while (!isSolved(nonets) && i < 81)
		{
			alanPalomo(nonets);
			printPuzzle(nonets);
			i++;
		}
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
	return decodeEntry(row, col, nonets)->getValue();	
}

Entry* decodeEntry(int row, int col, Nonet* nonets[9])
{
	int non_r = row / 3;
	int non_r2 = row % 3;
	int non_c = col / 3;
	int non_c2 = col % 3;
	
	return nonets[3 * non_r + non_c]->getEntry(3 * non_r2 + non_c2);	
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
	int x = 0;
	
	for (int i = 0; i < 81; i++)
	{
		if (i % 9 == 0)
		{
			cout << endl;
		}
		
		x = eightyOneGet(i / 9, i % 9, nonets);
		
		if (x)
		{
			cout << x << " ";
		}
		else
		{
			cout << "_ ";
		}
	}
	cout << endl;
}

void firstPass(Nonet* nonets[9])
{
	for (int i = 0; i < 9; i++)
	{
		removeChoicesInNonet(nonets[i]);
	}
	alanPalomo(nonets);
}

void removeChoicesInNonet(Nonet* nonet)
{
	Entry *y;
	int x = 0;
	
	for (int i = 0; i < 9; i++)
	{
		y = nonet->getEntry(i);
		
		for (int j = 0; j < 9 && !y->isSolved(); j++)
		{
			x = nonet->getEntry(j)->getValue();
			if (x != 0)
			{
				nonet->getEntry(i)->changePossible(x - 1);
			}
		}
	}
}


void alanPalomo(Nonet* nonets[9])
{	
	Entry *x, *y, *z = NULL;
	int value = 0;
	
	for (int j = 0; j < 9; j++)
	{
		for (int k = 0; k < 9; k++)
		{	
			z = decodeEntry(j, k, nonets);
			
			if (z->isSolved())
			{
				value = z->getValue();
				for (int i = 0; i < 9; i++)
				{
					x = decodeEntry(i, k, nonets);
					y = decodeEntry(j, i, nonets);
					
					if (x != NULL && !x->isSolved())
					{
						x->changePossible(value - 1);
					}
					if (y != NULL && !y->isSolved())
					{
						y->changePossible(value - 1);
					}
				}
			}
		}
	}
}

bool isSolved(Nonet *nonets[9])
{
	for (int i = 0; i < 9; i++)
	{
		if (!nonets[i]->isSolved())
		{
			return false;
		}
	}
	
	return true;
}