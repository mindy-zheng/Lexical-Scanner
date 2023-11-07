#include "token.h" 
#include "scanner.h"
#include <iostream>
#include <unordered_map> 
#include <fstream>
#include <stdlib.h> 
#include <string> 
#include <stdio.h> 

using namespace std; 

/* After designing FSA, represent the 2-d array representation for the FSA as array of integers

This FSA should recognize repeat operator and delimiter characters and stay in the respective state until recognized as a token. 

Implementing 2D FSA table: 
 * S0: Initial State
 * S1: Identifier 
 * S2-S3: Comment 
 * S4: Operator 
 * S5: Integer (FINAL: 1005) No sign or decimal point 
 * S6: Delimiter - ( ) { } ; , [ ] 
 * 1007: EOF 
 *   -1: Lexical Error 
*/ 

const int FSA_Table[7][27] = 
	// A-Z  a-z  0-9   WS     $     =    <<    >>    >    <    ~    :    ;    +    -    *    /    %    .    (    )    ,    {    }    [    ]  EOF 
/* S0 */ { -1,   1,   5,    0,    2,    4,    4,    4,   4,   4,   4,   6,   6,   4,   4,   4,   4,   4,   4,   6,   6,   6,   6,   6,   6,   6,1007}, 
/* S1 */ {  2,   2,   2, 1001, 1001, 1001, 1001, 1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001},  
/* S2 */ {  2,   2,   2,    2,    3,    2,    2,    2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2}, 	
/* S3 */ {1003,1003,1003,1003, 1003, 1003, 1003, 1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
/* S4 */ {1004,1004,1004,1004, 1004,    4, 1004, 1004,   4,   4,   4,1004,1004,   4,   4,   4,   4,   4,   4,1004,1004,1004,1004,1004,1004,1004,1004},
/* S5 */ {1005,1005,  5, 1005, 1005, 1005, 1005, 1005,1005,1005,1005,1005,1005,1005,  -1,1005,1005,1005,  -1,1005,1005,1005,1005,1005,1005,1005,1005},
/* S6 */ {1006,1006,1006,1006, 1006, 1006, 1006, 1006,1006,1006,1006,   6,   6,1006,1006,1006,1006,1006,1006,   6,   6,   6,   6,   6,   6,   6,1006},
}; 

