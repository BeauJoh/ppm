/* 
 * File:   filehandler.cpp
 * Author: beau
 * 
 * Created on October 14, 2009, 3:43 PM
 */

#include "filehandler.h"

fileHandler::fileHandler() {
    
}

// clears the file input buffer
void fileHandler::flushinput(istream & is)	{
	is.clear();
	char nextChar;
	while( (nextChar = is.get()) != '\n' && nextChar != EOF)
	{ }
	is.clear();
}

// establishes a ifstream connection to a file. The return value is 
// either true if the connection could be established and vice versa
bool fileHandler::fileOpen(ifstream& inFile, string fileName)
{
	bool success = false;


		inFile.open (fileName.data());

	if (inFile.is_open())	{
			success = true;
	}
	return success;
} 

// checks wether the file exists given a string as a Filename
// return value is wether the operation was successful or not
bool fileHandler::FileExists(string strFilename) { 
	struct stat stFileInfo; 
	bool blnReturn; 
	int intStat; 
	
	// Attempt to get the file attributes 
	intStat = stat(strFilename.c_str(),&stFileInfo); 
	if(intStat == 0) { 
		// We were able to get the file attributes 
		// so the file obviously exists. 
		blnReturn = true; 
	} else { 
		// We were not able to get the file attributes. 
		// This may mean that we don't have permission to 
		// access the folder which contains this file. If you 
		// need to do that level of checking, lookup the 
		// return values of stat which will give you 
		// more details on why stat failed. 
		blnReturn = false; 
	} 
	
	return(blnReturn); 
}

// collects input from keyboard and returns the complete string
// up until a new line is entered.
string fileHandler::betterCIN()	{
	string returnString;
	this->flushinput(cin);
	while (cin.peek() != '\n') {
		returnString += cin.get();
	}
	return returnString;
}

// establishes a ofstream connection to a file. The return value is 
// either true if the connection could be established else false
bool fileHandler::fileOpen (ofstream& outFile, string fileName) {
	bool success = false;

		outFile.open (fileName.data());

		if (outFile.is_open())  {
			success = true;
                }

   return success;
} 

// closes the ofstream and returns wether the connection was
// successfully closed or not
bool fileHandler::fileClose (ofstream& outFile) {
    bool success = true;
    outFile.close();
    if (outFile.is_open())  {
        success = false;
    }
    return success;
}

// closes the ifstream and returns wether the connection was
// successfully closed or not
bool fileHandler::fileClose (ifstream& inFile) {
    bool success = true;
    inFile.close();
    if (inFile.is_open())  {
        success = false;
    }
    return success;
}

// Checks wether the string is usable, return value indicative of this
bool fileHandler::stringNull(string a)  {
    if (a.empty())    {
        return true;
    }
    else if (a == "")   {
        return true;
    }
    else if (a == " \n")   {
        return true;
    }
    else if (a == "\n")   {
        return true;
    }
    else {
        return false;
    }
}


