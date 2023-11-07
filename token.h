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

enum tokenID { 
	ID_TOKEN = 1001, 
	KEYWORD_TOKEN = 1002,
	COMMENT_TOKEN = 1003, 
	OP_TOKEN = 1004,
	INTEGER_TOKEN = 1005, 
	DELIMITER_TOKEN = 1006, 
	EOF_TOKEN = 1007, 
	LEXICAL_ERROR = -1, 
};  


// 1001, 1002, etc could be final states recognizing different tokens...
const int finalState[] = {1001, 1002, 1003, 1004, 1005, 1006, 1007, -1}; 
	

typedef struct Token { 
	tokenID tokenType; 
	string tokenInstance; 
	int lineNumber; 
} Token; 

#endif

