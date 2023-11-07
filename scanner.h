#ifndef SCANNER_H
#define SCANNER_H 

#include <iostream>
#include "token.h" 

Token scanner(istream &input); 
int getColumn(char ch); 

#endif 
