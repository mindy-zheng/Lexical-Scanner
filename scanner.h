#ifndef SCANNER_H
#define SCANNER_H 

#include <iostream>
#include <string>
#include "token.h"

using namespace std; 
 

Token scanner(istream &file); // Get next token 
int getFSAColumn(char ch); 
void lexicalError(int lineNum); // Throws error 
Token createToken(string instance, int final_state); 
	

#endif 
