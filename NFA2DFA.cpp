#include "NFA2DFA.h"
#include <queue>
using namespace std;

// compute ε-closure
set<int> NFA2DFA::epsilonClosure(NFA & nfa, set<int> states) 
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

// Convert NFA to DFA using Subset Construction
DFA NFA2DFA::convert(NFA& nfa)
{
    DFA dfa;
    map<set<int>, int> stateMapping;
    queue<set<int>> processingQueue;

    set<int> startClosure = epsilonClosure(nfa, { nfa.getStartState() });
    stateMapping[startClosure] = 0;
    dfa.setStartState(0);
    processingQueue.push(startClosure);

    int dfaStateCounter = 1;

    while (!processingQueue.empty()) 
    {
        set<int> currentStates = processingQueue.front();
        processingQueue.pop();
        int dfaState = stateMapping[currentStates];

        for (char symbol : nfa.getAlphabet()) 
        {
            set<int> nextStates;

            for (int state : currentStates)
            {
                if (nfa.transitionTable.find({ state, symbol }) != nfa.transitionTable.end())
                {
                    nextStates.insert(nfa.transitionTable[{state, symbol}].begin(),
                        nfa.transitionTable[{state, symbol}].end());
                }
            }

            if (!nextStates.empty())
            {
                set<int> nextClosure = epsilonClosure(nfa, nextStates);

                if (stateMapping.find(nextClosure) == stateMapping.end()) 
                {
                    stateMapping[nextClosure] = dfaStateCounter++;
                    processingQueue.push(nextClosure);
                }

                dfa.addTransition(dfaState, symbol, stateMapping[nextClosure]);
            }
        }
    }
    // **Mark final states in the DFA**
    for (const auto& [nfaSet, dfaState] : stateMapping) 
    {
        for (int state : nfaSet) 
        {
            if (nfa.isFinalState(state))
            {
                dfa.addFinalState(dfaState);
                break;  // One final state is enough to mark DFA state as final
            }
        }
    }
    return dfa;
}
