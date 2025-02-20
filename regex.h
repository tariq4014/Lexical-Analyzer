#ifndef REGEX_H
#define REGEX_H

#include "NFA.h"
#include "DFA.h"
#include <string>

using namespace std;

class regex {
private:
    string pattern;              // Regex pattern
    string postfixPattern;       // Postfix form
    NFA nfa;                     // Generated NFA
    DFA dfa;                     // Generated DFA
    string InfixToPostfix(const string& infix);  // Convert infix to postfix

public:
    string getPostfixPattern();  // Get postfix pattern
    regex(string regexPattern);  // Constructor
};

#endif