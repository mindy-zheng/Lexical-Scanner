CS4280 Programming Translation Project -- P1:

Resubmission: 
This is a re-do of P1 with the correct FSA interpretation of the lexical definitions provided. 

I have choosen option 2: Tokens dont have to be separated by white spaces except when needed to prevent incorrect tokes (this will need FSA implementation or something similar)
Eg. 5+x doesnt need white spaces to figure this is integer followed by operator followed by ID
x y which is ID followed by ID must have the white space or otherwise it would be just one ID
Sources: 
1. This helped me in visualizing and creating my FSA table:  
	https://hackernoon.com/lexical-analysis-861b8bfe4cb0
2. This helped organized my tokenID's into key-value pairs: 
	https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/

I ran into some issues with P1_test3.f23 - This was hard for me to figure out. The scanner won't recognize 2> as separate tokens and put them together. I'll likely have to come into office hours for a 2nd pair of eyes on this. I'm stumped. 

HOW TO RUN: 
1. run and compile P1 with: make 

Option 1: Enter: ./P1 test1.f23 
	- or any testing file you'd like to use.
	- I created all testing files provided
	- Similar to P0, .f23 will be append if not provided by user 
Option 2: Enter: ./P1 
	- It will make a new line for you to enter input: 
	- example input: x xy xaw

I have 6 files: token.h, scanner.h, scanner.c, testScanner.c, testScanner.h, and main.c

