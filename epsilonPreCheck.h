#ifndef EPSILON_PRECHECK_H
#define EPSILON_PRECHECK_H

#include <string>
#include <vector>
#include <set>
using namespace std;

class NFA;

class epsilonPreCheck {
private:
    vector<NFA> vectorOfNFAs;  // Vector of NFAs

public:
    static set<string> isEpsilon(string input);  // Check epsilon transitions
};

#endif