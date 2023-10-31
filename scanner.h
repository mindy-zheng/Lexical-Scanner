#ifndef SCANNER_H
#define SCANNER_H 
#include <stdio.h> 
#include "token.h" 

void initializeScanner(FILE *file); 
Token nextToken(); // gets next Token
void freeToken(Token *token); 
const char* tokenName(int tokenID);
extern char* keywords[]; // Reserved keywords 
//int keywordDetected(char* str); // checks if str is a reserved keyword  

#endif 

// Initialize scanner with input file 
