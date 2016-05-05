#include "Entry.hpp"

class Nonet
{
	public:
		Nonet(void);
		void insertEntry(int place, int value);
		Entry* getEntry(int place);
		bool isSolved();
		
	private:
		Entry* entries[9];
};