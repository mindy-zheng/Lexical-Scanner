#ifndef SCANNER_H
#define SCANNER_H 

#include <iostream>
#include <string>
#include "token.h"

using namespace std; 

extern unordered_map<string, string> keyword_map; 
extern unordered_map<string, string> op_map; 
extern unordered_map<string, string> delimiter_map; 

 
int scanner(string &, Token &); 
int getFSAColumn(char ch); 
void lexicalError(int lineNum);
int opCheck(char ch);
int delCheck(char ch); 
int keywordCheck(Token &token); 
void init_maps(); 
void assignOp(Token &token); 
 

#endif 
