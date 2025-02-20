#include <queue>
#include "NFA.h"
int startingState;
set<char> alphabet;

NFA::NFA() 
{
    stateCounter = -1;
}

int NFA::createState()
{
    stateCounter = stateCounter + 1;
    return stateCounter;
}

int NFA::getStartState()
{
    return startingState;
}

set<char> NFA::getAlphabet()
{
    return alphabet;
}

// Function to add transitions dynamically
void NFA::addTransition(int fromState, char input, int toState)
{
    transitionTable[{fromState, input}].push_back(toState);
    alphabet.insert(input);
}

// Function to add e-transitions
void NFA::addEpsilonTransition(int fromState, int toState)
{
    transitionTable[{fromState, '_'}].push_back(toState);
}

bool NFA::isFinalState(int state)
{
    return acceptingStates.find(state) != acceptingStates.end();
}

void NFA::setStartState(int state)
{
    startingState = state;
}

void NFA::addFinalState(int state)
{
    acceptingStates.insert(state);
}

NFA NFA::concatenate(const NFA& nfa1, const NFA& nfa2) 
{
    NFA result;
    vector<int> newToStates;

    for (auto& transition : nfa1.transitionTable)
    {
        result.transitionTable[transition.first] = transition.second;
        result.alphabet.insert(transition.first.second);
    }
    int offset = nfa1.transitionTable.size()+1;
    for (auto& transition : nfa2.transitionTable)
    {
        pair<int, char> newKey = { transition.first.first + offset, transition.first.second };

        for (int toState : transition.second)
        {
            newToStates.push_back(toState + offset);
        }

        result.transitionTable[newKey] = newToStates;
        result.alphabet.insert(newKey.second);
        result.stateCounter = result.stateCounter + 2;
    }

    for (int finalState : nfa1.acceptingStates)
    {
        result.addEpsilonTransition(finalState, nfa2.startingState + offset);
    }

    result.startingState = nfa1.startingState;
    for (int state : nfa2.acceptingStates)
    {
        result.addFinalState(state+offset);
    }
    return result;
}

//Alternation: NFA1 | NFA2
NFA NFA::unionNFA(const NFA& nfa1, const NFA& nfa2) 
{
    NFA result;
    vector<int> newToStates;
    set<int> setOfStates;
    setOfStates.clear();
    int newStart = result.createState();
    setOfStates.insert(newStart);
    int offset1 = newStart + 1;
    
    newToStates.clear();
    //Ensure 'a' and 'b' transitions exist
    for (auto& transition : nfa1.transitionTable) 
    {
        pair<int, char> newKey = { transition.first.first + offset1, transition.first.second };

        for (int toState : transition.second) 
        {
            newToStates.push_back(toState + offset1);
        }

        result.transitionTable[newKey] = newToStates;
        result.alphabet.insert(newKey.second);
        setOfStates.insert(newKey.first);
        for (int states : newToStates)
        {
            setOfStates.insert(states);
        }
    }
    newToStates.clear();
    int offset2 = nfa1.transitionTable.size()+2;
    for (auto& transition : nfa2.transitionTable) 
    {
        pair<int, char> newKey = { transition.first.first + offset2, transition.first.second };

        for (int toState : transition.second)
        {
            newToStates.push_back(toState + offset2);
        }

        result.transitionTable[newKey] = newToStates;
        result.alphabet.insert(newKey.second);
        setOfStates.insert(newKey.first);
        for (int states : newToStates)
        {
            setOfStates.insert(states);
        }
    }
    result.stateCounter = setOfStates.size() - 1;
    int newFinal = result.createState();


    result.addEpsilonTransition(newStart, nfa1.startingState+offset1);
    result.addEpsilonTransition(newStart, nfa2.startingState + offset2);
    for (int finalState : nfa1.acceptingStates)
    {
        result.addEpsilonTransition(finalState+offset1, newFinal);
    }
    for (int finalState : nfa2.acceptingStates)
    {
        result.addEpsilonTransition(finalState + offset2, newFinal);
    }

    result.startingState = newStart;
    result.addFinalState(newFinal);

    return result;
}

//Kleene Star: NFA*
NFA NFA::kleeneStar(const NFA& nfa)
{
    NFA result;
    vector<int> newToStates;
    set<int> setOfStates;
    setOfStates.clear();
    int newStart = result.createState();
    setOfStates.insert(newStart);

    for (auto& transition : nfa.transitionTable)
    {
        pair<int, char> newKey = { transition.first.first + 1, transition.first.second };

        for (int toState : transition.second)
        {
            newToStates.push_back(toState + 1);
        }

        result.transitionTable[newKey] = newToStates;
        result.alphabet.insert(newKey.second);
        setOfStates.insert(newKey.first);
        for (int states : newToStates)
        {
            setOfStates.insert(states);
        }
    }

    result.stateCounter = setOfStates.size() - 1;
    int newFinal = result.createState();
    setOfStates.insert(newFinal);
    for (int finalState : nfa.acceptingStates) 
    {
        result.addEpsilonTransition(finalState+1, newFinal);
        result.addEpsilonTransition(finalState+1, nfa.startingState+1);
    }

    result.addEpsilonTransition(newStart, nfa.startingState+1);
    result.addEpsilonTransition(newStart, newFinal);

    result.startingState = newStart;
    result.addFinalState(newFinal);

    return result;
}

set<int> NFA::epsilonClosure(NFA& nfa, set<int> states)
{
    set<int> closure = states;
    queue<int> toProcess;

    for (int state : states) toProcess.push(state);

    while (!toProcess.empty())
    {
        int current = toProcess.front();
        toProcess.pop();

        if (nfa.transitionTable.find({ current, '_' }) != nfa.transitionTable.end())
        {
            for (int nextState : nfa.transitionTable[{current, '_'}])
            {
                if (closure.find(nextState) == closure.end())
                {
                    closure.insert(nextState);
                    toProcess.push(nextState);
                }
            }
        }
    }
    return closure;
}

bool NFA::isAccepted(NFA& nfa, const string& input)
{
    set<int> currentStates = NFA::epsilonClosure(nfa, { nfa.getStartState() });
    map<pair<int, char>, vector<int>> transitionTable1 = nfa.getTransitionTable();
    for (char c : input) 
    {
        set<int> nextStates; // Stores all possible next states

        // Iterate over all currently active states
        for (int state : currentStates) 
        {
            // Check if this state has transitions on `c`

            if (transitionTable1.find({ state, c }) != transitionTable1.end()) 
            {
                for (int nextState : transitionTable1[{state, c}])
                {
                    nextStates.insert(nextState);  
                }
            }
        }

        // Compute ε-closure for the newly reached states
        currentStates = NFA::epsilonClosure(nfa, nextStates);

        // If no valid states exist, reject input early
        if (currentStates.empty()) return false;
    }

    //Check if any of the final states is an accepting state
    for (int state : currentStates) 
    {
        if (nfa.acceptingStates.count(state) > 0)
        {
            return true;
        }
    }

    return false; // No accepting state reached
}

void NFA::displayNFA() 
{
    cout << "\n=== NFA Debug Information ===\n";

    // Display Start State
    cout << "Start State: " << startingState << endl;

    // Display Transitions
    cout << "Transitions:" << endl;
    for (const auto& transition : transitionTable)
    {
        int fromState = transition.first.first;
        char input = transition.first.second;
        for (int toState : transition.second)
        {
            if (input == 'e') 
            {  // Display epsilon as ''
                cout << "  " << fromState << " -- e --> " << toState << endl;
            }
            else
            {
                cout << "  " << fromState << " -- " << input << " --> " << toState << endl;
            }
        }
    }

    // Display Accepting States
    cout << "Accepting States: { ";
    for (int state : acceptingStates)
    {
        cout << state << " ";
    }
    cout << "}\n";
}

map<pair<int, char>, vector<int>> NFA::getTransitionTable()
{
    return transitionTable;
}
