#include "token.h" 
#include "scanner.h"
#include <iostream>
#include <fstream> 
#include <stdlib.h> 
#include <string> 

using namespace std;

/* After designing FSA, represent the 2-d array representation for the FSA as array of integers

This FSA should recognize repeat operator and delimiter characters and stay in the respective state until recognized as a token.
*/  

typedef enum {
	LEXICAL_ERROR = -1, 
	s1 = 0, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, s21, s22,
	FINAL = 1001, 
} states; 

const int max_keywords = 11; 
const char *keywords[] = { 
	"xopen", "xclose", "xloop", "xdata", "xexit", "xin", "xout", "xcond", "xthen", "xlet", "xfunc"}; 
const int max_length = 8; // for int constants and keywords
int lineNum = 1; 

const int FSA_Table[23][25] = 
{
         // a-z   A-Z   0-9    WS     =     <     >     ~     :     ;     +     -     *     /     %     .     (     )     ,     {     }     [     ]     $   EOF   
/* S1  */ {  s2,  -1,    s3,   s1,   s4,   s5,   s6,   s7,   s8,   s9,  s10,  s11,  s12,  s13,  s14,  s15,  s16,  s17,  s18,  s19,  s20,  s21,  s22, 1001, 1001},
/* S2  */ {  s2,  -1,    s2, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},  
/* S3  */ {1001, 1001,   s3, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},  
/* S4  */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001}, 
/* S5  */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001}, 
/* S6  */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S7  */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S8  */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S9  */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S10 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S11 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S12 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S13 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S14 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S15 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S16 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S17 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S18 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S19 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S20 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S21 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S22 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
/* S23 */ {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},
};

character next_ch; 
character filter(istream &FILE) { 
	character input; 
	char ch = FILE.get(); 
	int col = getFSAColumn(ch);
	
	//DEBUG: cout << "Current ch: " << ch << ", FSA Column: " << col << endl;

	while (col == COMMENT) { 
		do { 
			ch = FILE.get(); 
			if (ch == '\n') { 
				lineNum++; 
			}
		} while ( ch != '$'); 
		
		ch = FILE.get(); 
		col = getFSAColumn(ch); 
	} 

	if (col >= LOWERCASE && col <= END) { 
		input.value = ch; 
		input.FSAColumn = col; 
		input.lineNum = lineNum; 

		if (ch == '\n') { 
			lineNum++; 
		} 
		
		return input; 
	} else {
		lexicalError(lineNum); 
		exit(col); 
	}
}


void lookahead_ch(istream &FILE) { 
	next_ch = filter(FILE); 
} 

Token token; 

Token scanner(istream &FILE) { 
	states curr_state = s1; // initial state 
	
	//states next_state; 
	states next_state; 

	//Token token; 
	// store instance of token: 
	string instance = ""; 
	
	while (curr_state != 1001) { 
		next_state = static_cast<states>(FSA_Table[curr_state][next_ch.FSAColumn]); 
		//DEBUG: cout << "Current State: " << curr_state << ", Next State: " << next_state << ", Next Character: " << next_ch.value << endl;
		if (next_state == -1) {
			lexicalError(next_ch.lineNum); 
		}

		if (curr_state == 5 && next_ch.value == '>') {
            		next_ch = filter(FILE); // Move to the next character after '>'
            		instance = "<<"; // Set the instance to ">>"
            		next_state = FINAL; // Set the next state to the final state
        	}

		if (curr_state == 6 && next_ch.value == '<') {
            		next_ch = filter(FILE); // Move to the next character after '>'
            		instance = "<<"; // Set the instance to ">>"
            		next_state = FINAL; // Set the next state to the final state
        	}


		// Final state 
		if (next_state == FINAL) { 
			token.tokenType = static_cast<tokenID>(curr_state + max_keywords);
			token.tokenInstance = instance; 
			token.lineNumber = lineNum;

			//cout << "Token Instance: " << instance << ", Token ID: " << token.tokenType << endl;
			
			if (curr_state == s2) { 
				for (int i = 0; i < max_keywords; i++) { 
					if (keywords[i] == token.tokenInstance) { 
						token.tokenType = static_cast<tokenID>(i); 
						break;
					}
				}
			}
			return token; 
		} else { 
			if (next_ch.FSAColumn != WS) { 
				instance += next_ch.value;
			} 

			curr_state = next_state; 
			next_ch = filter(FILE); 
		
			if (instance.length() == max_length) { 
				//token.tokenType = static_cast<tokenID>(curr_state);
				token.tokenType = static_cast<tokenID>(curr_state + max_keywords);
				token.tokenInstance = instance; 
				token.lineNumber = next_ch.lineNum; 
				return token; 
			} 
		}
	}
	
	return token;

}

// a-z   A-Z   0-9    WS     =     <     >     ~     :     ;     +     -     *     /     %     .     (     )     ,     {     }     [     ]     $   EOF
/* 
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
*/ 
int getFSAColumn(char ch) {
	if (islower(ch)) { 
		return LOWERCASE;
	}
	if (isupper(ch)) { 
		return UPPERCASE;
	} 
	if (isdigit(ch)) { 
		return INTEGER;
	}
	if (isspace(ch)) { 
		return WS; 
	} 
	if (!islower(ch) && !isupper(ch) && !isdigit(ch) && !isspace(ch)) { 
		switch(ch) { 
			case '=': 
				return EQUAL; 
			case '<': 
				return LESS;
			case '>': 
				return GREATER; 
			case '~':
				return TILDE;
			case ':': 
				return COLON; 
			case ';': 
				return SEMICOLON;
			case '+': 
				return PLUS;
			case '-': 
				return MINUS; 
			case '*': 
				return MULTIPLY;
			case '/': 
				return DIVISION;
			case '%': 
				return PERCENT; 
			case '.': 
				return PERIOD;
			case '(': 
				return LPARENTHESIS;
			case ')': 
				return RPARENTHESIS;
			case ',':
				return COMMA;
			case '{': 
				return LBRACE;
			case '}': 
				return RBRACE; 
			case '[': 
				return LBRACKET;
			case ']':
				return RBRACKET;
			case EOF: 
				return END; 
			case '$': 
				return COMMENT;
			default: 
				return -1;
			}
	}
}

void lexicalError(int lineNum) { 
	cerr << "LEXICAL ERROR - line: " << lineNum << endl; 
} 

