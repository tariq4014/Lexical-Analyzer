#ifndef REGEX2NFA_H
#define REGEX2NFA_H

#include "NFA.h"
#include "DFA.h"
#include <string>

using namespace std;

class regex2NFA {
private:
    NFA nfa;  
    DFA dfa;  

public:
    NFA convertToNFA(string postfixPattern);  // Convert postfix to NFA
};

#endif