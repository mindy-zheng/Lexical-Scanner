CS4280 Programming Translation Project -- P1:

Resubmission: I made the mistake of not consistently checking the entireity of Project 1 View. I've been incredibly focused on my Operating Systems class which I have decided to take another semester. I'm sorry for not being able to fully be attentive to this course, but I finally have the time to, and intend to do my best. 
As for the P1 Lexical Definitions page, I wasn't checking this so I was sort of relying on my own interpretation of the P1 requirement specifications. That is of course my faul, and this was an honest mistake on my behalf, so I'm redoing the whole  project accordingly. I will detail the changes I make in a list. 

Sources: 
1. This helped me in helping me create my FSA table- 
	https://hackernoon.com/lexical-analysis-861b8bfe4cb0

Changes made: 
1. I relied heavily on provided lexical definitions. Before, I was assuming the lexical definitions based on C architecture instead of your requirements. 
2. 


 

I have choosen option 2: Tokens dont have to be separated by white spaces except when needed to prevent incorrect tokes (this will need FSA implementation or something similar)
Eg. 5+x doesnt need white spaces to figure this is integer followed by operator followed by ID
x y which is ID followed by ID must have the white space or otherwise it would be just one ID

HOW TO RUN: 
1. run and compile P1 with: make 
2. Enter: ./P1 test.f23 
	- or any testing file you'd like to use. 

I have 6 files: token.h, scanner.h, scanner.c, testScanner.c, testScanner.h, and main.c

token.h - defines the token type: tokenID, token instance, and line number
