CS4280 Programming Translation Project -- P1: 

I have choosen option 2: Tokens dont have to be separated by white spaces except when needed to prevent incorrect tokes (this will need FSA implementation or something similar)
Eg. 5+x doesnt need white spaces to figure this is integer followed by operator followed by ID
x y which is ID followed by ID must have the white space or otherwise it would be just one ID

I have 6 files: token.h, scanner.h, scanner.c, testScanner.c, testScanner.h, and main.c

token.h - defines the token type: tokenID, token instance, and line number 
