#ifndef SCANNER_H
#define SCANNER_H 

#include <iostream>
#include <string>
#include <fstream>
#include "token.h"
#include "scanner.h"

using namespace std; 

typedef struct character {
        char value;
        int FSAColumn;
        int lineNum;
} character;


Token scanner(istream &); 
character filter(istream &);
int getFSAColumn(char ch);
void lookahead_ch(istream &);  
void lexicalError(int lineNum);
void testScanner(ifstream &); 
void printToken(Token);  

// a-z   A-Z   0-9    WS     =     <     >     ~     :     ;     +     -     *     /     %     .     (     )     ,     {     }     [     ]     $   EOF
enum token_names {
	LOWERCASE, 
	UPPERCASE, 
	INTEGER, 
	WS, 
	EQUAL, 
	LESS, 
	GREATER,
	TILDE,
	COLON, 
	SEMICOLON, 
	PLUS,
	MINUS, 
	MULTIPLY,
	DIVISION,
	PERCENT,
	PERIOD,
	LPARENTHESIS,
	RPARENTHESIS,
	COMMA,
	LBRACE,
	RBRACE,
	LBRACKET,
	RBRACKET,
	COMMENT, 
	END
}; 

#endif 
