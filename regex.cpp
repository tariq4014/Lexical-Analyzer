#include <iostream>
#include <stack>
#include <string>
#include "NFA.h"
#include "regex.h"
using namespace std;

string regex::getPostfixPattern()
{
	return postfixPattern;
}

regex::regex(string regexPattern)
{
	postfixPattern = InfixToPostfix(regexPattern);

}

//---------------------------------------------------------------------
// define precedence and associativity of operators
//---------------------------------------------------------------------
int Precedence(char op)
{
	if (op == '*') return 3; // highest precedence for Kleene star (*)
	if (op == '.') return 2; // concatenation (.) has lower precedence than *
	if (op == '|') return 1; // alternation (|) has the lowest precedence
	return 0;
}
//---------------------------------------------------------------------
// check if a character is an operand (alpha)
//---------------------------------------------------------------------
bool IsOperand(char c)
{
	return isalpha(c);
}
//---------------------------------------------------------------------
// convert an infix regular expression to postfix
//---------------------------------------------------------------------
string regex::InfixToPostfix(const string& infix)
{
	stack<char> ops; // stack for operators
	string postfix = ""; // resulting postfix expression 'queue'
	for (size_t i = 0; i < infix.size(); i++)
	{
		char c = infix[i];
		if (IsOperand(c))
		{
			// if c is an operand, put it on the output queue
			postfix += c;
		}
		else if (c == '(')
		{
			// if it's an opening parenthesis, push it onto the stack
			ops.push(c);
		}
		else if (c == ')')
		{
			// pop off the stack until matching '(' is found
			while (!ops.empty() && ops.top() != '(')
			{
				postfix += ops.top();
				ops.pop();
			}
			ops.pop(); // pop the '('
		}
		else if (c == '|')
		{
			// if it's an alternation operator, pop operators of higher precedence
			while (!ops.empty() && ops.top() != '(' && Precedence(ops.top()) >=
				Precedence(c))
			{
				postfix += ops.top();
				ops.pop();
			}
			ops.push(c); // push the alternation operator onto the stack
		}
		else if (c == '.')
		{
			// do same for concatenation (.)
			while (!ops.empty() && ops.top() != '(' && Precedence(ops.top()) >=
				Precedence(c))
			{
				postfix += ops.top();
				ops.pop();
			}
			ops.push(c); // push the . operator onto the stack
		}
		else if (c == '*')
		{
			// and for (*)
			ops.push(c); // push the * operator onto the stack
		}
	}
	// pop all remaining operators off the stack
	while (!ops.empty())
	{
		postfix += ops.top();
		ops.pop();
	}
	return postfix;
}

