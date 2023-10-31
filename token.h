#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>

// Token types 
#define OP 1 
#define INT 2 
#define ID 3
#define KEYWORD 4 
#define NEWLINE 5
#define EOFTk 6

typedef struct { 
	int tokenID; 
	char *tokenInstance; 
	int lineNum; 
} Token;  

#endif

// Defining the structure of a token 
