/* 
 * File:   menuhandler.h
 * Author: beau
 *
 * Created on October 14, 2009, 11:37 AM
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <dirent.h> 

#include "sha1.h"
#include "pc1Handler.h"

using namespace std;

//main program control
class menuHandler {
public:
	
	// menuHandler constructor initializes the multi user logon function
    menuHandler();
	
	// changes the password of the current user, to the desired password. Reads and modifies, 
	// the users personal password depending if the existing password is valid if not the user
	//  is denied the right to change the password and returned to the user menu.
    void changePPM();
	
	// store a users specific values in the record directory. It is in an encrypted format
	// to keep it secure
    void addRecord();
	
	// return the unencrypted data from the record. Result is thrown to screen
    void retrieveRecord();
	
	// function removes a record located in the individual users Records directory.
	// no return type, if process failed throw an error to the screen.
	void deleteRecord();
	
	// display program terminating prompt
    void quit();
	
	// controls flow of the program accepting directions of the user
	// allows for the program to close, login with an existing user
	// or create a new user. Each user will have their own directory
	// containing their password allowing them to log in.
	// only one user name per directory... they must have a unique
	// qualifying id.
	void multiUserLogon();
	
	// to register a user, the user must enter in a logon name and 
	// password ... upon completion the user will have a directory,
	// with their own unique password and Files and Records directory
	bool registerUser();
	
	// this function compares the hash value of the password stored in the users password
	// directory, and compares it to the hashed value of what the user just entered.
	// if a match occurs they are allowed into the system. Else logon returns false and they
	// denied access to the user menu
    bool logon();
	
	// standard menu function. Once allowed access to the system users can have access to
	// their own files, to change their password, add remove or view their records. or encrypt
	// and decrypt their own files
    void menu();
	
	// records to be shown must be single word records... That is 
	// no whitespaces in record names expected!
	//
	// if all records contain no white spaces this function
	// will do a system call to retrieve all the records in the
	// record directory
	// this names will each individually be opened
	// and the filenames and the contents of the file
	// will be thrown to the screen. The contents of the file will remain
	// encrypted and displayed in hexidecimal format.
	void retrieveAllRecords();
	
	// A file must be in the users private directory called Files in order for the 
	// function to detect the correct file. There is no return type.  The user 
	// must enter the name of the file located in their Files directory, they wish to encrypt. 
	// the output file will be the filename with .enc appended to the end. This encrypted file
	// will be located in the same directory Files.
	void encryptAfile();
	
	// A file must be in the users private directory called Files in order for the 
	// function to detect the correct file.
	void decryptAfile();
	
	// this menu operates exactly the same way as the standard adminMenu function
	// excepting this is for the system admin, and consequently has an addition feature
	// to view all the names of system users.
	void adminMenu();
	
	// this function is used by the system administrator, to get a listing of all
	// the users of the system. The result is thrown to the screen.
	void viewAllSystemUsers();
	
private:
	// specifies pc1Handler for encrytion, decrytion functions, and fsteam functions 
	//for ease of use
    fileHandler file;
    ifstream fin;
    ofstream fout;
	pc1Handler crypter;
};

