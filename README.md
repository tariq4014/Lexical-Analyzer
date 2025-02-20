# Configurable Lexical Analyzer

This repository contains a configurable lexical analyzer (lexer) implemented in C++. The lexer processes input strings by matching them against user-defined token patterns (regular expressions) and outputs token-lexeme pairs, making it adaptable to various languages or data formats.

## Project Overview

A lexical analyzer converts a sequence of characters into tokens, where each token is defined by a regular expression and paired with its matching lexeme (e.g., `t1, "a"`). Unlike a fixed lexer, this configurable version allows users to specify token definitions, enhancing flexibility without modifying the core code.

### Example
**Input:**
t1 a|b, t2 a*, t3 (a|b)*, c  # 
"a aa bbc aad aa"
**Output:**
t1, "a",
t2, "aa",
t3, "bbc",
t2, "aa"
ERROR

## Requirements

- **Language**: C++ (compiled with `g++ -std=c++17`)
- **Input**: A list of token definitions (`token_name regex, ... #`) followed by an input string in quotes, read from stdin.
- **Output**: Token-lexeme pairs written to stdout, with `ERROR` or `EPSILON IS NOT A TOKEN` for invalid cases.
- **Regex Support**: Uses regular expressions as defined in class (e.g., `a|b`, `a*`, `(a|b)*.c`).


## Implementation Guide

The lexer was developed incrementally:
1. **Initial Stage**: Built a simple lexer with hardcoded Deterministic Finite Automata (DFAs).
2. **NFA-to-DFA Conversion**: Added functionality to convert Non-deterministic Finite Automata (NFAs) to DFAs.
3. **Regex Parsing**: Integrated a parser to interpret user-defined regular expressions and construct NFAs.

This modular approach ensured a working system at each step, progressively enhancing its capabilities.

## Setup and Usage

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/tariq4014/Lexical-Analyzer.git

2. **Compile**:
    g++ -std=c++17 $(find Lexical-Analyzer -name "*.cpp")

3. **Run**:
    Use a text file (e.g., test_1.txt) with token definitions and input string:
      t1 a|b, t2 a*.a, t3 (a|b)*.c*.c  #
      "a aac bbc aabc"
   
    Execute:
       ./a.out < test_1.txt > output.txt

    Expected output:
        t1, "a"
        t3, "aac"
        t3, "bbc"
        t3, "aabc"
   

