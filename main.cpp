#include "testScanner.h"
#include <iostream> 
#include <iomanip>
#include <fstream> 
using namespace std; 

int main(int argc, char *argv[]) {
        string file;

	if (argc > 1) { 
		file = string(argv[1]); // stores command line argument
                // If last 4 characters aren't .f23, then append .f23
                if (file.substr(file.size()-4) != ".f23") {
                	file += ".f23";
        }
	
	// Pass file to testScanner
	
	ifstream inFile(file); 
	if (!inFile) { 
		cerr << "Error: file not found" << endl; 
		return 1; 
	} 
	testScanner(inFile); 
	inFile.close(); 
	} else { 
		// if no filename, grab user input: 
		testScanner(cin); 
	}
	return 0; 
}

