#include "token.h"
#include "scanner.h" 
#include "testScanner.h" 
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>  

void testScanner() { 
	Token token; 
	while (true) { 
		token = nextToken(); 
		
		printf("Token ID: %d - %s\n", token.tokenID, tokenName(token.tokenID));
        	printf("Token Instance: %s\n", token.tokenInstance);
        	printf("Line Number: %d\n", token.lineNum);

		freeToken(&token); 

		if (token.tokenID == EOFTk) { 
			break; 
		} 
	}
} 
