#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "DFA.h"
#include "NFA.h"
#include "NFA2DFA.h"
#include "regex.h"
#include "regexParser.h"
#include "regex2NFA.h"

using namespace std;

map<string, DFA> regexParser::tokenDefinitions;

map<string, DFA> regexParser::regexParserFunction(const string& line)
{
    stringstream ss(line);
    string token, tokenName, regexDef;

    while (ss >> token) 
    {
        if (token == "," || token == "#")
        {
            continue;
        }

        if (token.back() == ',' || token.back() == '#') 
        {
            token.pop_back();  // Remove trailing commas or hash
        }

        if (token[0] == 't') 
        {  // Token name assumed to start with 't'
            tokenName = token;
        }
        else 
        
        {
            regexDef = token;
        }

        // Convert regex to NFA and then to DFA
        regex regexObj(regexDef);
        regex2NFA regexConverter;
        NFA nfa = regexConverter.convertToNFA(regexObj.getPostfixPattern());
        NFA2DFA NFAconverter;
        DFA dfa = NFAconverter.convert(nfa);

        // Store DFA in map using tokenName as key
        tokenDefinitions[tokenName] = dfa;
    }

    return tokenDefinitions;
}
