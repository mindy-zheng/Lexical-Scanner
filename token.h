// TOKEN HEADER
// Make sure to include in other files 
#ifndef TOKEN_H
#define TOKEN_H 

#include <iostream> 
#include <string> 
#include <unordered_map> 
#include <map> 

using namespace std; 

enum tokenID {
	// ID, INT, EOF: 
	EOF_TOKEN, 
	IDENTIFIER_TOKEN,
	INTEGER_TOKEN, 
	
	//Keywords
	XOPEN_TOKEN, 
	XCLOSE_TOKEN, 
	XLOOP_TOKEN, 
	XDATA_TOKEN, 
	XEXIT_TOKEN, 
	XIN_TOKEN, 
	XOUT_TOKEN, 
	XCOND_TOKEN,
	XTHEN_TOKEN, 
	XLET_TOKEN,
	XFUNC_TOKEN,

	// Operators: =, >>, <<, >, <, ~, +, -, *, /, %
	EQUAL_TOKEN,
	GREATERGREATER_TOKEN, 
	LESSLESS_TOKEN,
	GREATER_TOKEN,
	LESS_TOKEN, 
	TILDE_TOKEN, 
	PLUS_TOKEN, 
	SUBTRACT_TOKEN, 
	MULTIPLY_TOKEN, 
	DIVIDE_TOKEN, 
	PERCENT_TOKEN, 
	
	// Delimiters: :, ;, ., ',', (, ), {, }, [, ]
	COLON_TOKEN, 
	SEMICOLON_TOKEN, 
	PERIOD_TOKEN, 
	COMMA_TOKEN, 
	LPARENTHESIS_TOKEN,
	RPARENTHESIS_TOKEN, 
	LBRACE_TOKEN, 
	RBRACE_TOKEN, 
	LBRACKET_TOKEN,
	RBRACKET_TOKEN
};

typedef struct Token { 
	tokenID tokenType; 
	string tokenInstance; 
	int lineNumber; 
} Token; 

#endif

