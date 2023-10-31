#include "token.h" 
#include "scanner.h" 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h> 

FILE* input; 

const char *tokenName(int tokenID) { 
	switch (tokenID) { 
		case 1: return "Operator"; 
		case 2: return "Integer"; 
		case 3: return "Identifier"; 
		case 4: return "End of File"; 
		default: return "Not identified"; 
	}
}

/*char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for",
    "goto", "if", "int", "long", "register", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

int keywordDetected(char *str) { 
	int keyword_count = sizeof(keywords) / sizeof(char*); 

	for (int j = 0; j < keyword_count; j++) { 
		if (strcmp(str, keywords[j]) == 0) { 
			return 1;
		} 
	}
	return 0; 
} 
*/ 
void freeToken(Token *token) {
    free(token->tokenInstance);
    token->tokenInstance = NULL;
}
 

void initializeScanner(FILE *file) { 
	input = file; 
} 

Token nextToken() { 
	Token token; 
	int state = 0; 
	char tokenInstance[256]; // Buffer
	memset(tokenInstance, 0, sizeof(tokenInstance)); 
	char c; 
	int i = 0; // Index for token Instance 
	int lineNum = 1; // counter 
//`	char operators [] = "+-*/"; // Operators for OP state 

	// Implement Finite State Automaton: 
	while (true) { 
		c = fgetc(input); 
		if (c == EOF) { 
			if( i > 0) { 
			if (state == 1) {
                    		token.tokenID = INT;
                	} else if (state == 2) {
                    		token.tokenID = ID;
                	}
                token.tokenInstance = strdup(tokenInstance);
                token.lineNum = lineNum;
                return token;
            }
            // Set EOF token and line number
            	token.tokenID = EOFTk;
            	token.tokenInstance = NULL;
            	token.lineNum = lineNum;
            	return token;		
		} 

		if (c == '\n') {
                        printf("Newline at line %d\n", lineNum);
			lineNum++;
                }

		if (isspace(c)) { 
			if( i > 0) {
                        	if (state == 1) {
                                	token.tokenID = INT;
                        	} else if (state == 2) {
                               		token.tokenID = ID;
                        	}
                	token.tokenInstance = strdup(tokenInstance);
                	token.lineNum = lineNum;
                	return token;
            	}
		continue; 
		} 

		switch (state) {
			// Initial State 
			case 0: 
				if (isdigit(c)) { 
					state = 1; // Integer State 
					tokenInstance[i++] = c; 
				} else if (isalpha(c)) { 
					state = 2; // Identifier State
					tokenInstance[i++] = c; 
				} else if (c=='+') { 
					token.tokenID = OP; // ID = Operator
					// char str[2] = {c, '\0'}; 
					//token.tokenInstance = strdup(str)
					token.tokenInstance = strdup("+");
					token.lineNum = lineNum;  
					return token; 
				}
 
				break; 
			// Integer state
			case 1: 
				if (isdigit(c)) { 
					tokenInstance[i++] = c; 
				} else { 
					ungetc(c, input); // Unread last char
					state = 0; 
					token.tokenID = INT; // Integer token 
					token.tokenInstance = strdup(tokenInstance); // set instance to the int string 
					memset(tokenInstance, 0, sizeof(tokenInstance)); 
					i = 0; 
					token.lineNum = lineNum; 
					return token; 
				}  
				break;
			// Identifier state 
			case 2: 
				if (isalpha(c) || isdigit(c)) { 
					tokenInstance[i++] = c; 
				} else { 
					ungetc(c, input); 
					state = 0; 
					token.tokenID = ID; 
					token.tokenInstance = strdup(tokenInstance); 
					memset(tokenInstance, 0, sizeof(tokenInstance)); 
					i = 0; 
					token.lineNum = lineNum; 

					// check if the ID is a reserved keyword
				/*	if (keywordDetected(keywords)) { 
						token.tokenID = KEYWORD; 
					} else { 
						token.tokenID = ID; 
					} 
					token.tokenInstance = keywords;
				*/  
					return token; 
				} 
				break; 
				} 
		if (i > 0) { 
			token.lineNum = lineNum; 
		} 
	}
	if (c == EOF) { 
		token.tokenID = EOFTk; // End of file 
		token.tokenInstance = strdup("EOF"); 
		return token; 
	} 

	Token errorToken; 
	errorToken.tokenID = -1; 
	errorToken.tokenInstance = NULL; 
	errorToken.lineNum = -1; 
	return errorToken; 
	 
} 
