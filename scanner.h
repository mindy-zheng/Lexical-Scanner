#ifndef SCANNER_H
#define SCANNER_H 

#include <iostream>
#include <string>
#include "token.h"

using namespace std; 
 
void printFSATable(int col, int state);
Token scanner(istream &file); // Get next token
int getFSAColumn(char ch); 
void lexicalError(int lineNum); // Throws error
Token createToken(string instance, int final_state); 
char filter(istream &file);
tokenID convertIntToTokenID(int state); 
	

#endif 
