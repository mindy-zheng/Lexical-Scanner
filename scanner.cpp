#include "token.h" 
#include "scanner.h"
#include <iostream>
#include <fstream>
#include <cctype>  
#include <fstream>
#include <stdlib.h> 
#include <string> 
#include <stdio.h>
#include <unordered_map> 

using namespace std;

/* After designing FSA, represent the 2-d array representation for the FSA as array of integers

This FSA should recognize repeat operator and delimiter characters and stay in the respective state until recognized as a token. 

S1 - ID_TOKEN; S2 - INTEGER_TOKEN; S3 - OPERATOR_TOKEN; S4 - DELIMITER_TOKEN
Final States: ID - 1001, INT - 1002, OP - 1003, DEL - 1004, EOF - 1005
 */

const int FSA_Table[5][6] = { 
	//  A-Z   a-z   0-9    OP    WS   DEL   EOF
/* S0 */ {   -1,    1,    2,    3,    0,    4, 1005}, 
/* S1 */ {    1,    1,    1, 1001, 1001, 1001, 1001},
/* S2 */ { 1002, 1002,    2, 1002, 1002, 1002, 1002},
/* S3 */ { 1003, 1003, 1003, 1003, 1003, 1003, 1003},
/* S4 */ { 1004, 1004, 1004, 1004, 1004, 1004, 1004},
};

	// Specific state cases:
		// 1. No more than 8 characters for integer and identifiers
		// 2. Accept '>>' and '<<' as single token
		// 3. keyword identifier -- x followed by keyword
	
int current_index; // index for token 



int opCheck(char ch) { 
	for (int i = 0; i < 10; i++) { 
		if (ch == op[i]) { 
			return 1; 
		}
	}
	return 0; 
}

int delCheck(char ch) { 
	for (int i = 0; i < 9; i++) { 
		if (ch == delimiter[i]) { 
			return 1; 
		} 
	}
	return 0; 
}

int keywordCheck(Token &token) {
        for (int i = 0; i < 11; i++) {
                if (token.tokenInstance == keywords[i]) {
                        token.tokenInstance == KEYWORD_map[tokenInstance];
                        return i;
                }
        }
        return -1;
}

int getFSAColumn(char ch) {
	// Case: letter
	if (isalpha(ch)) {
		// lowercase letter 
		if (islower(ch)) { 
			return 1;
		} else { 
			return 0;; 
		} 
	} else if (isdigit(ch)) { 
		return 3; 
	} else if (opCheck(ch)) {
		return 4; 
	} else if (isspace(ch)) {
		return 5;
	} else if (delCheck(ch)) { 
		return 6; 
	} else { 
		return -1; 
	} 
}

void lexicalError(int lineNum) { 
	cerr << "LEXICAL ERROR - line: " << lineNum << endl; 
} 

void init_maps() { 
	keyword_map = {
		{"xopen", "xopen_tk"}, 
		{"xclose", "xclose_tk"}, 
		{"xloop", "xloop_tk"}, 
		{"xdata", "xdata_tk"}, 
		{"xexit", "xexit_tk"},
		{"xin", "xin_tk"},
		{"xout", "xout_tk"}, 
		{"xcond", "xcond_tk"},
		{"xthen", "xthen_tk"},
		{"xlet", "xlet_tk"}, 
		{"xfunc", "xfunc"} 
	}; 
	
	op_map = { 
		{"=", "equal_tk"}, 
		{"<", "lessthan_tk"}, 
		{">", "greaterthan_tk"}, 
		{"<<", "lessless_tk"}, 
		{">>", "greatergreater_tk"}, 
		{"~", "tilde_tk"}, 
		{"+", "plus_tk"}, 
		{"-", "minus_tk"}, 
		{"*", "mult_tk"}, 
		{"/", "slash_tk"}, 
		{"%", "percent_tk"}, 
		{".", "period_tk"}
	};

	delimiter_map = { 
		{":", "colon_tk"}, 
		{";", "semicolon_tk"}, 
		{"(", "lparenth_tk"}, 
		{")", "rparenth_tk"}, 
		{",", "comma_tk"}, 
		{"{", "lbracket_tk"}, 
		{"}", "rbracket_tk"}, 
		{"[", "lbrace_tk"}, 
		{"]", "rbrace_tk"}
	};
}

void assignOp(Token &token) { 
	token.tokenInstance.assign(op_map[token.tokenInstance]);
}

