#include "token.h" 
#include "scanner.h"
#include <iostream>
#include <unordered_map> 
#include <fstream>
using namespace std; 

/* After designing FSA, represent the 2-d array representation for the FSA as array of integers
 * 0, 1, etc would be states (using rows if states counted from 0)
 * -1, -2, etc. could be different errors
 *  1001, 1002, etc could be final states recognizing different tokens
 *  Merge keywords with IDs in the automaton, then do a table lookup if ID is detected
 
Implementing FSA table: 
*/ 



