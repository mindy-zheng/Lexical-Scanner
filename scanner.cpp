#include "token.h" 
#include "scanner.h"
#include <iostream>
#include <fstream>
#include <cctype>  
#include <fstream>
#include <stdlib.h> 
#include <string> 
#include <stdio.h> 

using namespace std; 

/* After designing FSA, represent the 2-d array representation for the FSA as array of integers

This FSA should recognize repeat operator and delimiter characters and stay in the respective state until recognized as a token. 

Implementing 2D FSA table: 
 * S0: Initial State
 * S1: Identifier 
 * S2-S3: Comment - No spaces 
 * S4: Operator 
 * S5: Integer (FINAL: 1005) No sign or decimal point 
 * S6: Delimiter - ( ) { } ; , [ ] 
 * 1007: EOF 
 *   -1: Lexical Error 
*/ 

const int FSA_Table[7][27] = { 
	// A-Z  a-z  0-9   WS     $     =    <<    >>    >    <    ~    :    ;    +    -    *    /    %    .    (    )    ,    {    }    [    ]  EOF 
/* S0 */ { -1,   1,   5,    0,    2,    4,    4,    4,   4,   4,   4,   6,   6,   4,   4,   4,   4,   4,   4,   6,   6,   6,   6,   6,   6,   6,1007}, 
/* S1 */ {  2,   2,   2, 1001, 1001, 1001, 1001, 1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001},  
/* S2 */ {  2,   2,   2, 1001,    3,    2,    2,    2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2}, 	
/* S3 */ {1003,1003,1003,1003, 1003, 1003, 1003, 1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
/* S4 */ {1004,1004,1004,1004, 1004,    4, 1004, 1004,   4,   4,   4,1004,1004,   4,   4,   4,   4,   4,   4,1004,1004,1004,1004,1004,1004,1004,1004},
/* S5 */ {1005,1005,  5, 1005, 1005, 1005, 1005, 1005,1005,1005,1005,1005,1005,1005,  -1,1005,1005,1005,  -1,1005,1005,1005,1005,1005,1005,1005,1005},
/* S6 */ {1006,1006,1006,1006, 1006, 1006, 1006, 1006,1006,1006,1006,   6,   6,1006,1006,1006,1006,1006,1006,   6,   6,   6,   6,   6,   6,   6,1006},
}; 

int lineNum = 1; 
const int max_length = 8; // No integer constant or ID should be over this 
const string keywords[] = { "xopen", "xclose", "xloop", "xdata", "xexit", "xin", "xout", "xcond", "xthen", "xlet", "xfunc" };
string prefix = ""; 

Token scanner(istream &file) { 
	int state = 0; // Start at initial state 
	int next_state = 0; 
	string instance; 
	Token token; 
	string str = prefix + ""; 

	while (state >= 0 && state < 1000) { 
		char ch = file.get(); // get next char 
		char next_ch = file.peek(); // peek at next char (for <<, >>) 
		int col = getFSAColumn(ch); 
		
		if (file.eof()) { 
			return createToken("", EOF_TOKEN); 
		}
		
		if (col == -1) { 
			token.tokenType = LEXICAL_ERROR; 
			token.tokenInstance = str + ch; 
			token.lineNumber = lineNum; 
			return token; 
		} 
		// Specific state cases:
		// 1. No more than 8 characters for intege and identifiers
		// 2. >> & <<
		// 3. keyword identifier -- x followed by keyword
				
		if ((ch == '<' && next_ch == '<') || (ch == '>' && next_ch == '>')) { 
			instance += ch; 
			instance += next_ch; 
			file.get(); // next char
			col = getFSAColumn(next_ch); 
		} 
	
		// Get next state: 
		next_state = FSA_Table[state][col]; 
		
		// Identifier check 
		if (next_state == 1001 || next_state == 1005) { 
			instance += ch;
			
			if (instance.length() > max_length) { 
				token.tokenType = LEXICAL_ERROR; 
				token.tokenInstance = str; 
				token.lineNumber = lineNum; 
				return token; 
			} 
			// Check if ID is a reserved keyword 
			if (ch=='x') {
                		state = 1002; // A potential keyword
				instance = "x"; 
           		}
       		}

		
		if (state == 1002) {
			if (isalpha(ch)) { 
				instance += ch; 
			} else {
				if (identifyKeyword(instance)) { 
				//cout << "Keyword detected: " << instance << endl;
				//next_state = 1002; 
				token.tokenType = KEYWORD_TOKEN;
                        	token.tokenInstance = instance;
                        	token.lineNumber = lineNum;
                        	return token;
			} else { 
				state = 1001; 
			}
		}
		}
		
		cout << "Next state: " << next_state << endl; // Debug statement

	    	//Debug statement: cout << "ch: " << ch << ", state: " << state << ", next_state: " << next_state << ", instance: " << instance << endl;
		/*
		 if (next_state == 1002) {
                	token.tokenType = KEYWORD_TOKEN;
 			token.tokenInstance = instance;
 			token.lineNumber = lineNum;
 			return token;
                } */ 

		if (!isspace(ch)) { 
			instance += ch; 
		} 
		state = next_state; // update the current state 
		
		if (ch == '\n') { 
			lineNum++; 
		} 
	}
	// For all final tokens, create and return: 
	if (state >= 1000) { 
		return createToken(instance, state); 
	} else { 
		// for all lexical errors: 
		lexicalError(lineNum); 
		return Token{LEXICAL_ERROR, instance, lineNum}; 
	}
} 
	



Token createToken(string instance, int final_state) {
	Token tkn;
	
	// Final state tokens: 
	switch (final_state) { 
		case 1001: 
			tkn.tokenType = ID_TOKEN; 
			break; 
		case 1002:
            		tkn.tokenType = KEYWORD_TOKEN;
            		break;
        	case 1003:
            		tkn.tokenType = COMMENT_TOKEN;
            		break;
        	case 1004:
            		tkn.tokenType = OP_TOKEN;
           		break;
        	case 1005:
            		tkn.tokenType = INTEGER_TOKEN;
            		break;
        	case 1006:
            		tkn.tokenType = DELIMITER_TOKEN;
            		break;
       		case 1007:
            		tkn.tokenType = EOF_TOKEN;
            		break;
        	default:
            		tkn.tokenType = LEXICAL_ERROR;
            		break;
		}
	
		tkn.tokenInstance = instance; 
		tkn.lineNumber = lineNum; 
		return tkn;
}

bool identifyKeyword(const string &instance) { 
	for (const string &keyword : keywords) {
        //Check if the identifier matches a keyword or starts with 'x' and matches the rest of a keyword
        	if (instance == keyword || (instance[0] == 'x' && instance.substr(1) == keyword)) {
        		return true;
                }
        }
        return false;

	/*const string keywords[] = {
		"xopen", "xclose", "xloop", "xdata", "xexit", "xin", "xout", "xcond", "xthen", "xlet", "xfunc" }; 
	for (int i = 0; i < 11; i++) { 
		if (instance == keywords[i]) { 
			return true; 
		} 
	}

	return false; */
}

int getFSAColumn(char input) { 
	if (isalpha(input)) { 
		if (input == 'x') { 
			return 1;
		} else { 
			return 0; 
		} 
	} else if (isdigit(input)) { 
		return 2; 
	} else if (isspace(input)) { 
		return 3; 
	} else { 
		switch(input) {
			case '$': return 4; 
			case '=': return 5; 
			//case '<<': return 6; 
			//case '>>': return 7; 
			case '>': return 8; 
			case '<': return 9; 
			case '~': return 10; 
			case ':': return 11;
			case ';': return 12; 
			case '+': return 13; 
			case '-': return 14; 
			case '*': return 15; 
			case '/': return 16; 
			case '%': return 17;
			case '.': return 18; 
			case '(': return 19; 
			case ')': return 20; 
			case ',': return 21; 
			case '{': return 22;
			case '}': return 23; 
			case '[': return 24; 
			case ']': return 25;
			//case 'EOF': return 26;
		}
	} 
	return -1; // Lexical Error 
}

void lexicalError(int lineNum) { 
	cerr << "LEXICAL ERROR - line: " << lineNum << endl; 
} 

