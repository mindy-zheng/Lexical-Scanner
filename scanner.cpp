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
/* S2 */ {  2,   2,   2, 1001, 1001, 1001, 1001, 1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001}, 	
/* S3 */ {1003,1003,1003,1003, 1003, 1003, 1003, 1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
/* S4 */ {1004,1004,1004,1004, 1004, 1004, 1004, 1004,   4,   4,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004},
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
		char ch = file.get(); 
		int col = getFSAColumn(ch);
		
		cout << "Character: " << ch << ", Column: " << col << ", State: " << state << ", Next State: " << next_state << ", String: " << str << endl;
		// Specific state cases:
		// 1. No more than 8 characters for integer and identifiers
		// 2. Accept '>>' and '<<' as single token
		// 3. keyword identifier -- x followed by keyword

	
		if (file.eof()) {
			return createToken("", EOF_TOKEN);
		}
	
		if (col == -1) { 
			token.tokenType = LEXICAL_ERROR; 
			token.tokenInstance = str + ch; 
			token.lineNumber = lineNum; 
			return token;  
		}

		next_state = FSA_Table[state][col]; 
		//cout << "Current state: " << state << ", Next state: " << next_state << endl;
		// Check if state transitioned
		if (state != next_state) {
			cout << "State transitioned from " << state << " to " << next_state << endl;
	 	}

		if (!isspace(ch)) str += ch; 
	
		// Final state checker: 
		if (next_state == ID_TOKEN || next_state == KEYWORD_TOKEN || next_state == COMMENT_TOKEN || next_state == OP_TOKEN || next_state == INTEGER_TOKEN || next_state == DELIMITER_TOKEN || next_state == EOF_TOKEN) {
			//cout << "Final state: " << next_state << ", Token string: " << str << endl;
			if (!str.empty()) { 
				token = createToken(str, next_state); 
				str = ""; 
				state = 0; 
				return token; 
			}
		}
		
		state = next_state; 

		if (next_state == 1003) { 
			str = ""; 
			next_state = 0; 
			state = 0; 
		} 
		
		if (next_state >= 1000 || next_state < 0) {
			string tokenInstance = str; 
			token = createToken(tokenInstance, next_state); 
			return token; 
		}  

		if (ch == '\n') lineNum++;

		}
		token.tokenType = LEXICAL_ERROR; 
		token.tokenInstance = str;
                token.lineNumber = lineNum;	 
		
		return token; 
		}  
		
Token createToken(string instance, int final_state) {
	cout << "Creating token with instance: " << instance << endl;
	Token token;
	
	// Final state tokens: 
	switch (final_state) {
		// Check for keywords here:  
		case 1001: 
			for (const string &keyword : keywords) {
                		if (keyword.compare(instance) == 0) {
                    			token.tokenType = KEYWORD_TOKEN;
					break;
			} else { 
				token.tokenType = ID_TOKEN;
			}
		}
		// check if identifier exceeds 8 characters: 
		if (instance.length() > max_length) { 
			cout << "This exceeds 8 max characters" << endl; 
			token.tokenType = LEXICAL_ERROR;
		}
		break;  
		case 1002:
            		token.tokenType = KEYWORD_TOKEN;
            		break;
        	case 1003:
            		token.tokenType = COMMENT_TOKEN;
            		break;
        	case 1004:
            		token.tokenType = OP_TOKEN;
           		break;
        	case 1005:
			// Check for integer exceeding 8 integers: 
			if (instance.length() > max_length) { 
				cout << "This exceeds 8 max characters" << endl;
                        	token.tokenType = LEXICAL_ERROR;
            		} else {
				token.tokenType = INTEGER_TOKEN;
			}
            		break;
        	case 1006:
            		token.tokenType = DELIMITER_TOKEN;
            		break;
       		case 1007:
            		token.tokenType = EOF_TOKEN;
            		break;
        	default:
            		token.tokenType = LEXICAL_ERROR;
            		break;
		}
	
		token.tokenInstance = instance;
		//cout << "Token Instance: " << token.tokenInstance << endl; 
		token.lineNumber = lineNum; 
		return token;
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
		}
	} 
	return -1; // Lexical Error 
}

void lexicalError(int lineNum) { 
	cerr << "LEXICAL ERROR - line: " << lineNum << endl; 
} 

