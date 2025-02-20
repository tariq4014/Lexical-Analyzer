#include "lexer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

// Constructor
Lexer::Lexer(map<string, DFA> givenTokenDef, string inputText)
{
    tokenDef = givenTokenDef;
    input = inputText;
}

// Tokenize input
void Lexer::lexme()
{
    vector<string> testWords;
    stringstream ss(input);
    string word;

    while (ss >> word)
    {
        if (word.front() == '\"')
        {
            word.erase(0, 1);
        }
        if (word.back() == '\"')
        {
            word.pop_back();
        }
        testWords.push_back(word);
    }

    int errors = 0;
    bool inAlpha = false;
    for (auto it = testWords.begin(); it != testWords.end(); ++it)
    {
        const string& word = *it;
        for (auto charIt = word.begin(); charIt != word.end(); ++charIt)
        {
            char c = *charIt;
            inAlpha = false;
            for (auto tokenIt = tokenDef.begin(); tokenIt != tokenDef.end(); ++tokenIt)
            {
                if (tokenIt->second.isInAlph(c))
                {
                    inAlpha = true;
                    break;
                }
            }
            if (!inAlpha)
            {
                inAlpha = false;
                break;
            }
        }
        if (inAlpha)
        {
            size_t i = 0;
            while (i < word.size())
            {
                string longestMatch = "";
                string matchedToken = "";
                size_t matchLength = 0;

                for (size_t j = i; j < word.size(); j++)
                {
                    string currentMatch = word.substr(i, j - i + 1);
                    for (auto tokenDefIt = tokenDef.begin(); tokenDefIt != tokenDef.end(); ++tokenDefIt)
                    {
                        DFA dfa = tokenDefIt->second;
                        if (dfa.isAccepted(currentMatch))
                        {
                            longestMatch = currentMatch;
                            matchedToken = tokenDefIt->first;
                            matchLength = j - i + 1;
                            break;
                        }
                    }
                }
                if (!matchedToken.empty())
                {
                    cout << matchedToken << " , \"" << longestMatch << "\"" << endl;
                    i += matchLength;
                }
                else
                {
                    i++;
                }
            }
        }
        else
        {
            errors++;
        }
    }
    for (int i = 0; i < errors; ++i)
    {
        cout << "ERROR" << endl;
    }
}