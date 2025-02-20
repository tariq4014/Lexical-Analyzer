#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "DFA.h"
#include "NFA.h"
#include "regex.h"
#include "regexParser.h"
#include "regex2NFA.h"
#include "epsilonPreCheck.h"

// Check for epsilon transitions
set<string> epsilonPreCheck::isEpsilon(string input)
{
    map<string, NFA> tokenDefinitions;
    stringstream ss(input);
    string token, tokenName, regexDef;

    while (ss >> token)
    {
        if (token == "," || token == "#")
        {
            continue;
        }

        if (token.back() == ',' || token.back() == '#')
        {
            token.pop_back();
        }

        if (token[0] == 't')
        {
            tokenName = token;
        }
        else
        {
            regexDef = token;
        }

        regex regexObj(regexDef);
        regex2NFA regexConverter;
        NFA nfa = regexConverter.convertToNFA(regexObj.getPostfixPattern());
        tokenDefinitions[tokenName] = nfa;
    }

    string epsilon = "_";
    set<string> epsilonRules;
    for (auto it = tokenDefinitions.begin(); it != tokenDefinitions.end(); ++it)
    {
        if (NFA::isAccepted(it->second, epsilon))
        {
            epsilonRules.insert(it->first);
        }
    }
    return epsilonRules;
}