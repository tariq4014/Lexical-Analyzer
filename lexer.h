#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <map>
#include "DFA.h"
#include "NFA.h"
#include "NFA2DFA.h"
#include "regex.h"

using namespace std;

class Lexer {
private:
    map<string, DFA> tokenDef;  // Token definitions as DFAs
    string input;               // Input string to tokenize

public:
    Lexer(map<string, DFA> givenTokenDef, string inputText);  // Constructor
    void lexme();  // Tokenize input
};

#endif