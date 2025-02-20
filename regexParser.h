#ifndef REGEXPARSER_H
#define REGEXPARSER_H

#include <iostream>
#include <map>
#include "DFA.h"

using namespace std;

class regexParser {
public:
    static map<string, DFA> regexParserFunction(const string& line);  // Parse regex to <token name, DFA>

private:
    static map<string, DFA> tokenDefinitions;  // Token definitions
};

#endif