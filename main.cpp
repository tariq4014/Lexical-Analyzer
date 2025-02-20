#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "lexer.h"
#include "regexParser.h"
#include "epsilonPreCheck.h"

using namespace std;
map<string, DFA> tokenDefinitions;
string token, testWords;

int main() 
{
    // Step 1: Convert the regular expression to a DFA and pair it with its name e.g. <t1, a|b>
    if (getline(cin, token))
    {
        set<string> epsilonRules = epsilonPreCheck::isEpsilon(token);
        if (!epsilonRules.empty())
        {
            cout << "EPSILON IS NOT A TOKEN";
            for (string epsilonRule : epsilonRules)
            {
                cout << " " << epsilonRule;
            }

            return 0;
        }
        tokenDefinitions = regexParser::regexParserFunction(token);
    }

    // Step 2: Takes the token definitions and the input characters and validate them
    if (getline(cin, testWords))
    {       
        Lexer lexer(tokenDefinitions, testWords);
        lexer.lexme(); 
    }
    return 0;
}
