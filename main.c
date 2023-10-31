#include "scanner.h"
#include "token.h" 
#include "testScanner.h" 
#include <stdio.h> 

int main(int argc, char **argv) { 
	FILE *input; 
	if (argc < 2) { 
		printf("Error, needs filename\n"); 
		return 1; 
	} else { 
		input = fopen(argv[1], "r"); // read file
		if (input == NULL) { 
			printf("Error when opening file: %s\n", argv[1]); 
			return 1; 
		} 
	} 

	initializeScanner(input); 

	testScanner(); 
	
	fclose(input); 

	return 0; 



}
