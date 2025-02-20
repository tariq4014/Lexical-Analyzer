#include <iostream>
#include <stack>
#include <string>
#include "NFA.h"
#include "regex2NFA.h"


NFA regex2NFA::convertToNFA(string postfixPattern)
{
	stack<NFA> nfaStack;  // Stack to store NFAs while processing

	for (char c : postfixPattern)
	{
		if (isalpha(c)) 
		{
			// Create an NFA for a single character
			NFA singleNFA;
			int start = singleNFA.createState();
			int end = singleNFA.createState();
			singleNFA.addTransition(start, c, end);
			singleNFA.setStartState(start);
			singleNFA.addFinalState(end);
			nfaStack.push(singleNFA);
		}
		else if (c == '.') 
		{
			//Concatenation (A . B)
			if (nfaStack.size() < 2) continue;
			NFA nfa2 = nfaStack.top(); nfaStack.pop();
			NFA nfa1 = nfaStack.top(); nfaStack.pop();
			NFA concatenatedNFA = NFA::concatenate(nfa1, nfa2);
			nfaStack.push(concatenatedNFA);
		}
		else if (c == '|')
		{
			// Alternation (A | B)
			if (nfaStack.size() < 2) continue;
			NFA nfa2 = nfaStack.top(); nfaStack.pop();
			NFA nfa1 = nfaStack.top(); nfaStack.pop();
			NFA unionNFA = NFA::unionNFA(nfa1, nfa2);
			nfaStack.push(unionNFA);
		}
		else if (c == '*') 
		{
			if (nfaStack.empty()) continue;
			NFA topNFA = nfaStack.top(); nfaStack.pop();
			NFA starNFA = NFA::kleeneStar(topNFA);
			nfaStack.push(starNFA);
		}
	}

	if (!nfaStack.empty())
	{
		nfa = nfaStack.top();  // Final NFA is on top of stack
	}
	return nfa;
}