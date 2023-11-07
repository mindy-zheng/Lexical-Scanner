#ifndef TEST_SCANNER_H 
#define TEST_SCANNER_H
#include <unordered_map>
#include <iostream> 
#include "token.h" 

using namespace std;
struct tokenID_hash { 
	size_t operator()(tokenID const& tokenID) const noexcept {
		return hash<int>()(static_cast<int>(tokenID)); 
	}
}; 

extern unordered_map<tokenID, string, tokenID_hash> token_names; 

void testScanner(istream &file);
Token scanner(istream &file);  

#endif
