#ifndef NFA2DFA_H
#define NFA2DFA_H

#include "NFA.h"
#include "DFA.h"

class NFA2DFA {
public:
    static set<int> epsilonClosure(NFA& nfa, set<int> states);  // Epsilon closure
    DFA convert(NFA& nfa);  // Convert NFA to DFA
};

#endif