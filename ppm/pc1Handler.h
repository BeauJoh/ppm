/*
 *  pc1Handler.h
 *  ppm5233
 *
 *  Created by Beau Johnston on 20/10/09.
 *  Copyright 2009 University Of New England. All rights reserved.
 *
 */
// Streaming cryption class... encrypts, decrypts and reads and writes to files.

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "pc1.h"
#include "filehandler.h"

using namespace std;

class pc1Handler {
public:
	
	// constructor initializes the cryptor with a new key
    pc1Handler();

	// Creates a new streaming cryption key and stores it
    void createKey();
	
	// Allocates and resizes the cstring size of the file 
	// required for it to be encrypted
    void initializeEncSize(char * fileData);
	
	// Allocates and resizes the cstring size of the file
	// required for it to be decrypted. Creates proper boundaries
	void initializeDecSize(char * fileData);
	
	// Utilizes fileHandler.h to open a file, passed as a filename
	// this file is open and read, and the result run though the
	// decryption stage. The resulting string is the decrypted data
	// contained within the file.
	string loadAndDecode(string fileName);
	
	// utilizes fileHandler functions to write data to a file.
	// accepts string values... the fileName to be written to
	// and the data to be written
	// the stored data is encrypted.
	void lockAndStock(string fileName, string data);
	
private:
	// creates its own stream cipher... its methods are used accordingly
	PukallCipher cipher;
	char *buf, key[100];
	int i, slen;
	
	// define the fileHandler methods, easier to recall
	fileHandler file;
    ifstream fin;
    ofstream fout;
};
