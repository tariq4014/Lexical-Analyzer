#ifndef DFA_H 
#define DFA_H

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

// DFA class for a Deterministic Finite Automaton
class DFA {
private:
    int startingState;                     // Start state
    set<char> alphabet;                    // Input symbols
    map<pair<int, char>, int> transitionTable;  // Transitions
    set<int> acceptingStates;              // Final states

public:
    DFA();                                 // Default constructor
    void setStartState(int newStartState); // Set start state
    void addTransition(int fromState, char input, int toState); // Add transition
    bool isAccepted(string& input);        // Check if string is accepted
    void addFinalState(int state);         // Add accepting state
    bool isInAlph(char c);                 // Check if char is in alphabet
    void displayDFA();                     // Display DFA
};

#endif 