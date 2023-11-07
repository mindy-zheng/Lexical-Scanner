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
/* S2 */ {  2,   2,   2,   -1,    3,    2,    2,    2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2}, 	
/* S3 */ {1003,1003,1003,1003, 1003, 1003, 1003, 1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
/* S4 */ {1004,1004,1004,1004, 1004,    4, 1004, 1004,   4,   4,   4,1004,1004,   4,   4,   4,   4,   4,   4,1004,1004,1004,1004,1004,1004,1004,1004},
/* S5 */ {1005,1005,  5, 1005, 1005, 1005, 1005, 1005,1005,1005,1005,1005,1005,1005,  -1,1005,1005,1005,  -1,1005,1005,1005,1005,1005,1005,1005,1005},
/* S6 */ {1006,1006,1006,1006, 1006, 1006, 1006, 1006,1006,1006,1006,   6,   6,1006,1006,1006,1006,1006,1006,   6,   6,   6,   6,   6,   6,   6,1006},
}; 

int lineNum = 1; 
const int max_length = 8; // No integer constant or ID should be over this 
string prefix = ""; 

Token scanner(istream &file) { 
	int state = 0; // Start at initial state 
	int next_state = 0; 
	string instance; 
	Token token; 
	string str = prefix + ""; 

	while (state > = 0 && state < 1000) { 
		char ch = file.get(ch); // get next char 
		char next_ch file.peek(); // peek at next char (for <<, >>) 
		int col = getFSAColumn(ch); 
		
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
			if (ch == '<') { 
				col = 6; 
			} else { 
				col = 7; 
			} 
			file.get(); 
		} 
		
		// Get next state: 
		next_state = FSA_Table[state][col]; 
		if ((next_state == 1001 || next_state == 1005) && str.length() > 8) { 
			token.tokenType = LEXICAL_ERROR; 
			token.tokenInstance = str; 
			token.lineNumber = lineNum; 
			return token; 
		} 
		if (next_state == 1001 && str[0] == 'x' && identifyKeyword(str)) { 
			next_state == 1002; 
		} 

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
		return Token{Lexical_ERROR, instance, lineNum}; 
	}
} 
	



Token createToken(string instance, int finalState) {
	Token tkn;
	
	// Final state tokens: 
	switch (final_state) { 
		case 1001: 
			token.type = ID_TOKEN; 
			break; 
		case 1002:
            		tkn.type = KEYWORD_TOKEN;
            		break;
        	case 1003:
            		tkn.type = COMMENT_TOKEN;
            		break;
        	case 1004:
            		tkn.type = OP_TOKEN;
           		break;
        	case 1005:
            		tkn.type = INTEGER_TOKEN;
            		break;
        	case 1006:
            		tkn.type = DELIMITER_TOKEN;
            		break;
       		case 1007:
            		tkn.type = EOF_TOKEN;
            		break;
        	default:
            		tkn.type = LEXICAL_ERROR;
            		break;
		}
	
		tkn.instance = instance; 
		tkn.lineNum = lineNum; 
		return tkn;
}

bool identifyKeyword(const string &str) { 
	const string keywords[] = {
		"xopen", "xclose", "xloop", "xdata", "xexit", "xin", "xout", "xcond", "xthen", "xlet", "xfunc" }; 
	for (const string &keyword: keywords) { 
		if (str == keyword) { 
			return true; 
		}
	}
	return false; 
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
			case 'EOF': return 26;
		}
	}
}

void lexicalError(int lineNum) { 
	cerr << "LEXICAL ERROR - line: " << lineNum << endl; 
} 

