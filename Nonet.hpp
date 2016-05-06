#include "Entry.hpp"

class Nonet
{
	public:
		Nonet(void);
		void insertEntry(int place, int value);
		Entry* getEntry(int place);
		void checkForLonersAndSolveThemIfTheyExist();
		void removeChoices();
		bool isSolved();
		
	private:
		Entry* entries[9];
};