#include "Entry.hpp"

class Nonet
{
	public:
		Nonet(void);
		void insertEntry(int nonet_row, int nonet_col, int value);
		Entry* getEntry(int nonet_row, int nonet_col);
		bool isSolved();
		
	private:
		Entry* entries[3][3];
		bool solved;
};