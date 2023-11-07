#include "testScanner.h"
#include "token.h"  
#include  <iostream> 
using namespace std; 

// Matching tokenID using unordered map
unordered_map<tokenID, string, tokenID_hash> token_names = {
        { ID_TOKEN, "Identifier"},
        { COMMENT_TOKEN, "Comment" },
        { KEYWORD_TOKEN, "Keyword"},
        { OP_TOKEN, "Operator"},
        { INTEGER_TOKEN, "Integer"},
        { DELIMITER_TOKEN, "Delimiter"},
        { EOF_TOKEN, "EOF"},
        { LEXICAL_ERROR, "Lexical Error"}
};

void testScanner(istream &file) { 
	Token token = scanner(file); 
	while(true) {
		//Print descriptive token followed by line number followed by token instance (string) if any then \n 
		cout << "Token ID: " << token_names[token.tokenType] << endl; 
		cout << "Line Number: " << token.lineNumber << endl; 
		cout << "Token Instance: " << token.tokenInstance << endl;
		cout << " ------------- " << endl;  

		if (token.tokenType == 1007) { 
			break; 
		} 
		token = scanner(file); // invoke next token 
	}
} 
