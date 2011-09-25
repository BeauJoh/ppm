/* 
 * File:   filehandler.h
 * Author: beau
 *
 * Created on October 14, 2009, 3:43 PM
 */
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <cstdlib>
#include <sys/stat.h> 
using namespace std;

class fileHandler {
public:
	// constructor does nothing
    fileHandler();
	
	// clears the file input buffer
	void flushinput(istream & is);	
	
	// establishes a ifstream connection to a file. The return value is 
	// either true if the connection could be established and vice versa
    bool fileOpen (ifstream& inFile, string fileName);
	
	// checks wether the file exists given a string as a Filename
	// return value is wether the operation was successful or not
	bool FileExists(string strFilename);
	
	// collects input from keyboard and returns the complete string
	// up until a new line is entered.
	string betterCIN();
	
	// establishes a ofstream connection to a file. The return value is 
	// either true if the connection could be established else false
    bool fileOpen (ofstream& outFile, string fileName);
	
	// closes the ofstream and returns wether the connection was
	// successfully closed or not
    bool fileClose (ofstream& outFile);
	
	// closes the ifstream and returns wether the connection was
	// successfully closed or not
    bool fileClose (ifstream& inFile);
	
	// Checks wether the string is usable, return value indicative of this
    bool stringNull(string a);
		
private:
    
};


