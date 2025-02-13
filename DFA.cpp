#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

class DFA
{
private:
	int startingState;
	set<char> alphabet;
	map<pair<int, char>, int> transitionTable;
	set<int> accepteningState;

public:
	DFA()
	{
		startingState = 0;

		alphabet.insert('a');
		alphabet.insert('b');

		transitionTable[{0, 'a'}] = 1;
		transitionTable[{0, 'b'}] = 1;
		transitionTable[{1, 'a'}] = 1;
		transitionTable[{1, 'b'}] = 1;

		accepteningState.insert(1);
	}

	bool isAccepted(string& input)
	{
		int correntState = startingState;
		for (char c : input)
		{
			if (alphabet.find(c) != alphabet.end() && transitionTable.find({ correntState, c }) != transitionTable.end())
			{
				correntState = transitionTable[{correntState, c}];
			}
			else
			{
				return false;
			}
		}
		return accepteningState.count(correntState) >= 0;
	}
};