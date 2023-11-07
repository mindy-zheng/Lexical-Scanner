#ifndef SCANNER_H
#define SCANNER_H 

#include <iostream>
#include "token.h" 

Token scanner(); // Get next token 
int getFSAColumn(char ch); 
void lexicalError(int lineNum); // Throws error 

#endif 
