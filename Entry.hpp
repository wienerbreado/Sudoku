class Entry		// Holds the number, if solved, and array of possible numbers if not solved.
{
	public:
		Entry(int value);
		Entry(void);
		void changePossible(int number);
		bool isPossible(int number);
		bool isSolved();
		int getValue();
	
	private:
		int value;
		int possible[9];
		bool solved;
};