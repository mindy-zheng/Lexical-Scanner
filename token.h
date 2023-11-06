// TOKEN HEADER
// Make sure to include in other files 
#ifndef TOKEN_H
#define TOKEN_H 

#include <iostream> 
#include <string> 

using namespace std; 

enum TokenType { 
	IDENTIFIER,
	INTEGER, 
	COMMENT, 
	LEXICAL_ERROR, 

	// KEYWORDS: Start with X, then KEYWORD: 
	XOPEN, 
	XCLOSE,
	XLOOP,
	XDATA,
	XEXIT,
	XDATA,
	XIN,
	XOUT, 
	XCOND, 
	XTHEN, 
	XLET,
	XFUNC, 
	
	// OPERATORS
	OP_GT, // >
	OP_LT, // <
	OP_COLON, // :
	OP_EQUAL, // = 
	OP_LESSTHAN, // << 
	OP_GREATERTHAN, // >> 
	OP_MULTIPLY, // *
	OP_DIVISION, // / 
	OP_MINUS, // - 
	OP_TILDE, // ~
	OP_SEMICOLON, // ;
	OP_PERCENT, // %
	OP_PERIOD, // .
	OP_LEFTP, // ( 
	OP_RIGHTP, // ) 
	OP_COMMA, // , 
	OP_LEFTB, // { 
	OP_RIGHTB, // } 
	OP_LEFTSQ, // [
	OP_RIGHTSQ, // ]
	
	EOF_TOKEN, 
} 

struct Token { 
	TokenType token ID; 
	string tokenInstance; 
	int lineNum; 
}; 

#endif

