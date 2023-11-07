#include "token.h" 
#include "scanner.h"
#include <iostream>
#include <fstream> 
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

const int FSA_Table[7][27] = 
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
const int length = 8; // No integer constant or ID should be over this 
ifstream file; 

Token scanner() { 
	int state = 0; // Start at initial state 
	string instance; 
	
	while (true) { 
		char ch = file.get(); // get next char 
		if (ch == '\n') { lineNum++; } // increment line number every time WS 
		
		int col = getFSAColumn(ch); 
		
		// get next state: 
		state = FSA_Table[state][col]; 

		// state cases: 
		if (state == -1) { 
			lexicalError(lineNum); 
			return Token{LEXICAL_ERROR, instance, lineNum}; 
		} else if (state >= 1000) { 
			// final state cases
			return Token{(TokenType)(state-1000), instance, lineNum}; 
		} else { 
			instance += ch; 
		}
	}
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

