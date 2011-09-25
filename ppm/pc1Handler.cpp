/*
 *  pc1Handler.cpp
 *  ppm5233
 *
 *  Created by Beau Johnston on 20/10/09.
 *  Copyright 2009 University Of New England. All rights reserved.
 *
 */

#include "pc1Handler.h"

// constructor initializes the cryptor with a new key
pc1Handler::pc1Handler()	{
	this->createKey();
}

// Creates a new streaming cryption key and stores it
void pc1Handler::createKey(){
	char * createdKey = new char[100];
	for (int i = 0; i < 100; i ++)	{
		createdKey[i] = i;
	}
	strcpy(key, createdKey);
}

// Allocates and resizes the cstring size of the file 
// required for it to be encrypted
void pc1Handler::initializeEncSize(char * fileData)	{
	slen = (int)strlen(fileData);
	cipher.plainlen=slen;
	cipher.ascipherlen=2*cipher.plainlen;
}

// Allocates and resizes the cstring size of the file
// required for it to be decrypted. Creates proper boundaries
void pc1Handler::initializeDecSize(char * fileData)	{
	slen = (int)strlen(fileData);
	cipher.plainlen= slen / 2;
	cipher.ascipherlen= slen;
}


// Utilizes fileHandler.h to open a file, passed as a filename
// this file is open and read, and the result run though the
// decryption stage. The resulting string is the decrypted data
// contained within the file.
string pc1Handler::loadAndDecode(string fileName)	{
	string theResult;
	string data;
	
	// data collected from file
	file.fileOpen(fin, fileName);
	
	while(!fin.eof())	{
		getline(fin, data);
		theResult += data;
	}
	if(!fin.eof()){
		cerr << "Error reading\n";
		return "";
	}
	file.fileClose(fin);
	
	// file data is converted from a string to a cstring
	char * fileData = new char[theResult.size()];
	fileData = (char*)theResult.data();
	
	// data is then decrypted and the returned result is the decrypted data
	this->initializeDecSize(fileData);
	cipher.ascCipherText = fileData;
	cipher.ascii_decrypt128(fileData, key);
	theResult = cipher.plainText;
	return theResult;
	
}

// utilizes fileHandler functions to write data to a file.
// accepts string values... the fileName to be written to
// and the data to be written
// the stored data is encrypted.
void pc1Handler::lockAndStock(string fileName, string data)	{
	// open the output file and await to be written
	file.fileOpen(fout, fileName);
	
	// convert the data into a cstring. Required for encryption!
	char * fileData = new char[data.size()];
	fileData = (char*)data.data();
	
	// encrypt the data
	this->initializeEncSize(fileData);
	cipher.ascii_encrypt128(fileData, key);
	
	// store the data in the file and close it.
	fout.write(cipher.ascCipherText, data.size()*2);
	file.fileClose(fout);
}

