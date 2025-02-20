#include "DFA.h"

// Constructor
DFA::DFA()
{
}

// Set start state
void DFA::setStartState(int newStartState)
{
    startingState = newStartState;
}

// Add transition
void DFA::addTransition(int fromState, char input, int toState)
{
    transitionTable[{fromState, input}] = toState;
    alphabet.insert(input);
}

// Check if string is accepted
bool DFA::isAccepted(string& input)
{
    int currentState = startingState;
    for (auto it = input.begin(); it != input.end(); ++it)
    {
        char c = *it;
        if (alphabet.find(c) != alphabet.end() && transitionTable.find({ currentState, c }) != transitionTable.end())
        {
            currentState = transitionTable[{currentState, c}];
        }
        else
        {
            return false;
        }
    }
    for (auto it = acceptingStates.begin(); it != acceptingStates.end(); ++it)
    {
        int state = *it;
        if (state == currentState)
        {
            return true;
        }
    }
    return false;
}

// Add final state
void DFA::addFinalState(int state)
{
    acceptingStates.insert(state);
}

// Check if char is in alphabet
bool DFA::isInAlph(char charToBeChecked)
{
    for (auto it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        char c = *it;
        if (charToBeChecked == c)
        {
            return true;
        }
    }
    return false;
}

// Display DFA
void DFA::displayDFA()
{
    cout << "DFA Transition Table:" << endl;
    for (auto it = transitionTable.begin(); it != transitionTable.end(); ++it)
    {
        int fromState = it->first.first;
        char input = it->first.second;
        int toState = it->second;
        cout << "  " << fromState << " -- " << input << " --> " << toState << endl;
    }
    cout << "Start State: " << startingState << endl;
    cout << "Accepting States: { ";
    for (auto it = acceptingStates.begin(); it != acceptingStates.end(); ++it)
    {
        int state = *it;
        cout << state << " ";
    }
    cout << "}" << endl;
}