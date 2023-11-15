// TOKEN HEADER
// Make sure to include in other files 
#ifndef TOKEN_H
#define TOKEN_H 

#include <iostream> 
#include <string> 
#include <unordered_map> 

using namespace std; 

/*
 * 0, 1, etc would be states (using rows if states counted from 0)
 * -1, -2, etc. could be different errors
 * 1001, 1002, etc could be final states recognizing different tokens
 * Merge keywords with IDs in the automaton, then do a table lookup if ID is detected */

const char comment = '$'; 
const string token_names[6] = {"Identifier", "Keyword", "Operator", "Integer", "Delimiter", "End of File"}; 

// New Table should only have 6 states 

const char op[] = {'+', '-', '=', '>', '<', '~', '*', '/', '%', '.'}; 
extern unordered_map<string, string> op_map; 
const char delimiter[] = {':', ';', ')', '(', ',', '{', '}', '[', ']'};
extern unordered_map<string, string> delimiter_map;
const string keywords[11] = { "xopen", "xclose", "xloop", "xdata", "xexit", "xin", "xout", "xcond", "xthen", "xlet", "xfunc"};
extern unordered_map<string, string> keyword_map;

extern int current_index; 
extern int line_index; 
extern int token_index; 
 

// 1001, 1002, etc could be final states recognizing different tokens...
//const int finalState[] = {1001, 1002, 1003, 1004, 1005, 1006, 1007, -1}; 
	
enum tokenID {
        ID_TOKEN,
        KEYWORD_TOKEN,
        OP_TOKEN,
        INTEGER_TOKEN,
        DELIMITER_TOKEN,
        EOF_TOKEN,
        LEXICAL_ERROR,
};

typedef struct Token { 
	tokenID tokenType; 
	string tokenInstance; 
	int lineNumber; 
} Token; 


#endif

