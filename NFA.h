#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

class NFA {
private:
    int startingState;          // Start state
    set<char> alphabet;         // Input symbols
    set<int> acceptingStates;   // Final states
    int stateCounter;           // Tracks state IDs

public:
    map<pair<int, char>, vector<int>> transitionTable;  // Transitions
    NFA();                                 // Constructor
    int createState();                     // New state ID
    int getStartState();                   // Get start state
    void setStartState(int state);         // Set start state
    set<char> getAlphabet();               // Get alphabet
    void addTransition(int fromState, char input, int toState);  // Add transition
    void addEpsilonTransition(int fromState, int toState);       // Add epsilon transition
    void addFinalState(int state);         // Add final state
    bool isFinalState(int);                // Check if state is final
    static NFA concatenate(const NFA& nfa1, const NFA& nfa2);    // Concatenate NFAs
    static NFA unionNFA(const NFA& nfa1, const NFA& nfa2);       // Union of NFAs
    static NFA kleeneStar(const NFA& nfa);  // Kleene star
    static set<int> epsilonClosure(NFA& nfa, set<int> states);   // Epsilon closure
    static bool isAccepted(NFA& nfa, const string& input);       // Check if accepted
    map<pair<int, char>, vector<int>> getTransitionTable();      // Get transition table
    void displayNFA();                     // Display NFA
};

#endif