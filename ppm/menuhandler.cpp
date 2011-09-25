/* 
 * File:   menuhandler.cpp
 * Author: beau
 * 
 * Created on October 14, 2009, 11:37 AM
 */

#include "menuhandler.h"

// menuHandler constructor initializes the multi user logon function
menuHandler::menuHandler() {
	this->multiUserLogon();
}

// controls flow of the program accepting directions of the user
// allows for the program to close, login with an existing user
// or create a new user. Each user will have their own directory
// containing their password allowing them to log in.
// only one user name per directory... they must have a unique
// qualifying id.
void menuHandler::multiUserLogon()	{
	char choice;
    for(;;) {
		cout << "START MENU" << endl;
		cout << "0  to quit" << endl;
		cout << "1  to login" << endl;
		cout << "2  to register" << endl;
		cout << endl;
		cout << "Your choice:"  << endl;
		cin >> choice;
		
		if (choice == '0')  {
			this->quit();
			return;
		}
		else if (choice == '1')   {
			// prompts for the user to login to their directory
			// first checks to see if that directory exists... if not
			// user isn't yet registered to use the system.
			string userName;
			cout << "Enter your login name:" << endl;
			cin >> userName;
			if (chdir(userName.data()) != -1) {
				// if the file exists go to logon. and if their password is accepted
				// they are granted access to the system. If the user is an admin
				// go to a special admin menu else go to standard user menu
				
				bool hasAccessRights;
				hasAccessRights = this->logon();
				if (hasAccessRights)    {
					if (userName.compare("admin") == 0)	{
						this->adminMenu();	
					}
					else {
						this->menu();
					}
				}
				else    {
					// if the user dosnt have access rights then go back to
					// the multiuser logon
					cout << "Not the correct Password" << endl;
					cout << "             Goodbye..." << endl;
					sleep((int)2);
					chdir("..");
				}
			}
			else {
				// if the username is incorrect... go back to multiuser logon
				cout << "that user does not exist" << endl;
				sleep((int)1);
			}

		}
		else if (choice == '2') {
			// create a new user. invokes register user function
			this->registerUser();
		}
		else {
			// only accepts 3 choices, so stay in the multiUser logon
			cout << "That selection is invalid..." << endl;
			cout << "returning..." << endl;
			sleep((int)1);
		}
		cout << '\n' << '\n' << endl;
	}
	
}

// to register a user, the user must enter in a logon name and 
// password ... upon completion the user will have a directory,
// with their own unique password and Files and Records directory
bool menuHandler::registerUser()	{
	string userName;
	cout << "Enter a login name:" << endl;
	cin >> userName;
	cin.clear();
	// create a new directory with full access rights called the user's name
	if (mkdir(userName.data(), 999) != -1) {
		chdir(userName.data());
		mkdir("Records", 999);
		mkdir("Files", 999);
			
		bool passConsistent = false;
		cin.clear();
		
		// prompt the user to enter a new password, verify it, and store that
		// password back to the file in a hashed form. Finally return to multiUser logon
	while (!passConsistent) {
		string newRealPass;
            	cout << "Enter a new password: " << endl;
            	cin >> newRealPass;
			
            	string confirmRealPass;
            	cout << "Confirm the new password:  " << endl;
            	cin >> confirmRealPass;
			
            if (newRealPass.compare(confirmRealPass) == 0) {
                cout << "OK. Registration successful" << endl;
                file.fileOpen(fout, "pass");
                fout << sha1_string(confirmRealPass.data());
                file.fileClose(fout);
		
                passConsistent = true;
				chdir("..");
            }
            else{
                cout << "I'm sorry that password wasn't consistent" << endl;
                cout << "please try again..." << endl;
                sleep((int)2);
                cout << '\n' << '\n' << endl;
            }
		}		
		return true;
	}
	// if the user already exists just return to logon menu
	else {
		cout << "registration failed... that user already exists" << endl;
		sleep((int)1);
		return false;	
	}
	
}

// this function compares the hash value of the password stored in the users password
// directory, and compares it to the hashed value of what the user just entered.
// if a match occurs they are allowed into the system. Else logon returns false and they
// denied access to the user menu
bool menuHandler::logon()    {
	string trialPass;
 	bool didConnect = file.fileOpen(fin, "pass");
	if (!didConnect)    {
        didConnect = file.fileOpen(fout, "pass");
	fout << sha1_string((const char*)"firstUse");
        file.fileClose(fout);
	file.fileOpen(fin,"pass");
    }
	
	// collect everything from the users password file and store it in the real pass
	// this will later be compared to what the user put in. This value is the hashed password.
	string theRealPass((std::istreambuf_iterator<char>(fin)),(std::istreambuf_iterator<char>()));
    	file.fileClose(fin);

    	cout << "Enter your password: " << endl;
    	cin >> trialPass;

	// hash the password and compare it. If a match occurs the user is granted access to the system
	// if not ... access is denied. If the password is firstUse however... the system will prompt the user
	// to reset it.
	trialPass = sha1_string(trialPass.data());
	bool areEquivilent = false;
	if (theRealPass.compare(trialPass) == 0)	{
		areEquivilent = true;
	}
	
    if (areEquivilent)   {
        cout << "OK. Login successful. " << endl;
		
		// if the password is equal to its first use
        if (theRealPass.compare(sha1_string("firstUse")) == 0)  {
            // remove the old pass
            rmdir("pass");
            bool passConsistent = false;
			
			// make the user enter in the new password twice to verify it
			// if so ... store it in the users pass file.
            while (!passConsistent) {
				string newRealPass;
            	cout << "Enter a new ppm password: " << endl;
				cin >> newRealPass;

            	string confirmRealPass;
            	cout << "Confirm the new password:  " << endl;
            	cin >> confirmRealPass;

            if (newRealPass.compare(confirmRealPass) == 0) {
                cout << "OK. A new password is set for ppm." << endl;
                file.fileOpen(fout, "pass");
                fout << sha1_string((const char *)newRealPass.data());
                file.fileClose(fout);
                passConsistent = true;
            }
            else{
                cout << "I'm sorry that password wasn't consistent" << endl;
                cout << "please try again..." << endl;
                sleep((int)2);
                cout << '\n' << '\n' << endl;
            }
            }
    }
		// the user is allowed into the file
        return true;
    }
	// the user is not allowed access.
    return false;
}

// this menu operates exactly the same way as the standard adminMenu function
// excepting this is for the system admin, and consequently has an addition feature
// to view all the names of system users.
void menuHandler::adminMenu()	{
	char choice;
    for(;;) {
		cout << "MENU" << endl;
		cout << "0  to  quit" << endl;
		cout << "1  to  change the ppm password " << endl;
		cout << "2  to  enter a new record" << endl;
		cout << "3  to  retrieve a record" << endl;
		cout << "4  to show all encrypted records" <<endl;
		cout << "5  to encrypt a file" << endl;
		cout << "6  to decrypt a file" << endl;
		cout << "7  to delete a record " << endl;
		cout << "8  to view all ppm users" << endl;
		cout << endl;
		cout << "Your choice:"  << endl;
		cin >> choice;
		
		if (choice == '0')  {
			this->quit();
			chdir("..");
			return;
		}
		else if (choice == '1')   {
			this->changePPM();
		}
		else if (choice == '2') {
			this->addRecord();
		}
		else if (choice == '3') {
			this->retrieveRecord();
		}
		else if (choice == '4') {
			this->retrieveAllRecords();
		}	
		else if (choice == '5') {
			this->encryptAfile();
		}	
		else if (choice == '6') {
			this->decryptAfile();
		}	
		else if (choice == '7') {
			this->deleteRecord();
		}
		else if (choice == '8') {
			this->viewAllSystemUsers();
		}
		else {
			cout << "That selection is invalid..." << endl;
			cout << "returning..." << endl;
			sleep((int)1);
		}
		cout << '\n' << '\n' << endl;
	}
	
}

// this function is used by the system administrator, to get a listing of all
// the users of the system. The result is thrown to the screen.
void menuHandler::viewAllSystemUsers()	{
	// move a step back to the main resources directory open the current directory
	// store all the contents in the string variable theResult and print it to the screen.
	chdir("..");
	string theResult;
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d)	{
		while ((dir = readdir(d)) != NULL)
		{
			if( strcmp( dir->d_name, "." ) == 0 || 
			   strcmp( dir->d_name, ".." ) == 0 || strcmp(dir->d_name, ".DS_Store") == 0 ) {
				continue;
			}
			theResult += (string)dir->d_name;
			theResult += "\n";
		}
		closedir(d);
	}
	
	cout << "The users of the system are: " << endl;
	cout << theResult;
	chdir("admin");
}

// standard menu function. Once allowed access to the system users can have access to
// their own files, to change their password, add remove or view their records. or encrypt
// and decrypt their own files
void menuHandler::menu()    {
    char choice;
    for(;;) {
    cout << "MENU" << endl;
    cout << "0  to  quit" << endl;
    cout << "1  to  change the ppm password " << endl;
    cout << "2  to  enter a new record" << endl;
    cout << "3  to  retrieve a record" << endl;
	cout << "4  to show all encrypted records" <<endl;
	cout << "5  to encrypt a file" << endl;
	cout << "6  to decrypt a file" << endl;
	cout << "7  to delete a record " << endl;
    cout << endl;
    cout << "Your choice:"  << endl;
    cin >> choice;

    if (choice == '0')  {
        this->quit();
	chdir("..");
        return;
    }
    else if (choice == '1')   {
        this->changePPM();
    }
    else if (choice == '2') {
        this->addRecord();
    }
    else if (choice == '3') {
        this->retrieveRecord();
    }
	else if (choice == '4') {
        this->retrieveAllRecords();
    }	
	else if (choice == '5') {
        this->encryptAfile();
    }	
	else if (choice == '6') {
        this->decryptAfile();
    }	
	else if (choice == '7') {
		this->deleteRecord();
	}
    else {
        cout << "That selection is invalid..." << endl;
        cout << "returning..." << endl;
        sleep((int)1);
    }
	cout << '\n' << '\n' << endl;
}
}

// changes the password of the current user, to the desired password. Reads and modifies, 
// the users personal password depending if the existing password is valid if not the user
//  is denied the right to change the password and returned to the user menu.
void menuHandler::changePPM() {
	string trialPass;
	
	// open the users private pass file... if it dosnt exist create a new one... with the default password
	// first use
 	bool didConnect = file.fileOpen(fin, "pass");
	if (!didConnect)    {
        didConnect = file.fileOpen(fout, "pass");
	fout << sha1_string((const char*)"firstUse");
        file.fileClose(fout);
	file.fileOpen(fin,"pass");
    }
	
	// store everything from the password file into the string variable theRealPass
	// compare this hashed value to the hash of what the user entered. 
	string theRealPass((std::istreambuf_iterator<char>(fin)),(std::istreambuf_iterator<char>()));
    	file.fileClose(fin);

    cout << "Enter current ppm password:" << endl;
    cin >> trialPass;
	
	// hash what the user entered to be checked against
	trialPass = sha1_string(trialPass.data());
	
	bool areEquivilent = false;
	if (theRealPass.compare(trialPass) == 0)	{
		areEquivilent = true;
	}
      if (areEquivilent)   {
            // remove the old pass replace with the new password hash
            rmdir("pass");
            bool passConsistent = false;
		  while (!passConsistent) {
			  string newRealPass;
			  cout << "Enter a new ppm password: " << endl;
			  cin >> newRealPass;
			  
			  string confirmRealPass;
			  cout << "Confirm the new password:  " << endl;
			  cin >> confirmRealPass;
			  
			  if (newRealPass.compare(confirmRealPass) == 0) {
				  cout << "OK. A new password is set for ppm." << endl;
				  file.fileOpen(fout, "pass");
				  fout << sha1_string(newRealPass.data());
				  file.fileClose(fout);
				  passConsistent = true;
			  }
			  else{
                cout << "I'm sorry that password wasn't consistent" << endl;
                cout << "please try again..." << endl;
                sleep((int)2);
                cout << '\n' << '\n' << endl;
				  // get a consistent entry of the password to store
            }
            }
      }
      else{
		  // the old password was incorrect... they dont have rights to change the password
		  // so return to the menu without modifying anything
        cout << "Not the correct Password" << endl;
        cout << "Goodbye..." << endl;
        sleep((int)2);
        return;
    }
}

// store a users specific values in the record directory. It is in an encrypted format
// to keep it secure
void menuHandler::addRecord()    {
	// if the users Record directory dosnt exist ... create it
	// reguardless of this move into it and add a file
	if (chdir("Records") != 0)	{
		mkdir("Records", 999);
		chdir("Records");
	}
    string recordName;
    string password;
    cout << "Enter a name for the new record:" << endl;
	recordName = file.betterCIN(); 
	// get the file name and its data to be stored...

    if (file.stringNull(recordName))    {
        cout << "The Record Name cannot be empty" << endl;
		chdir("..");
        return;
    }
    cout << "Enter the password in the new record:" << endl;
	file.flushinput(cin);
	while (cin.peek() != '\n') {
		password += cin.get();
	}
	
    if (file.stringNull(password))    {
        cout << "The Record needs a password" << endl;
		chdir("..");
        return;
    }
	
	// encrypt the data and write it to the file.
	crypter.lockAndStock(recordName, password);
	
    cout << "OK. Record created" << endl;
	chdir("..");
}

// return the unencrypted data from the record. Result is thrown to screen
void menuHandler::retrieveRecord()   {
	// if the individual users Records directory does not exist, create it
	// reguardless, move into it
	if (chdir("Records") != 0)	{
		mkdir("Records", 999);
		chdir("Records");
	}
	
	// get the name of the record to be loaded...
    string record;
    cout << "Enter the name of the record:" << endl;
	file.flushinput(cin);
	while (cin.peek() != '\n') {
		record += cin.get();
	}

	// if a record has no name... throw appropriate error and exit
	if (file.stringNull(record)) {
		cout << "The Record cannot be empty" << endl;
		chdir("..");
        return;
	}
	
	// if that record dosnt not exist display appropriate message and exit
	string returnString = crypter.loadAndDecode(record);
	if (returnString.empty())    {
        cout << "That Record does not Exist" << endl;
		chdir("..");
        return;
    }
	
	// else display the contents of the record to screen
    cout << "The password is: " << endl;
	cout << returnString << endl;
	chdir("..");
}

// display program terminating prompt
void menuHandler::quit() {
    cout << "BYE" << endl;
	cout << '\n' << '\n' << endl;
	
}

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
void menuHandler::retrieveAllRecords()	{
	// if the individual users Records directory does not exist, create it
	// reguardless, move into it
	if (chdir("Records") != 0)	{
		mkdir("Records", 999);
		chdir("Records");
	}
	cout << "The encrypted passwords (in hex) are:" << endl;
	
	string theResult;

	// create a new directory variable to extract all the contents of the current directory
	// and append it to a string variable... theResult string
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d)	{
		while ((dir = readdir(d)) != NULL)
		{
			if( strcmp( dir->d_name, "." ) == 0 || 
			   strcmp( dir->d_name, ".." ) == 0 || 
			   strcmp(dir->d_name, ".DS_Store") == 0 ) {
				continue;
			}
			theResult += (string)dir->d_name;
			theResult += "\n";
		}
		closedir(d);
	}
	
	// now that all the filenames are collected pass the string though a
	// string stream... splitting the string by whitespace.
	// each substring will then be used to open each files contents and the
	// result... the data contained in each file ... will be thrown to the screen in
	// a hex format
    string str = theResult;
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words
	string outString;
	
    while (ss >> buf)	{
			file.fileOpen(fin, buf);
			fin >> outString;
			file.fileClose(fin);
			cout << buf << endl;
			cout << endl;
			for ( int i = 0; i < outString.size(); i++)	{
				printf("%.2x ", outString.at(i));
				i ++;
			}
			cout << endl;
			cout << endl;
			cout << endl;
			tokens.push_back(buf);
	}
	// finally return to the users main directory
	chdir("..");
}

// A file must be in the users private directory called Files in order for the 
// function to detect the correct file. There is no return type.  The user 
// must enter the name of the file located in their Files directory, they wish to encrypt. 
// the output file will be the filename with .enc appended to the end. This encrypted file
// will be located in the same directory Files.
void menuHandler::encryptAfile()	{
	// if the individual users Files directory does not exist, create it
	// reguardless, move into it
	if (chdir("Files") != 0)	{
		mkdir("Files", 999);
		chdir("Files");
	}
	cout << "Enter a file name: " << endl;
	string fileName;
	file.flushinput(cin);
	while (cin.peek() != '\n') {
		fileName += cin.get();
	}
	// if the file to encrypt has no name return to menu go back to private directory
	if (file.stringNull(fileName))    {
        cout << "The File cannot be empty" << endl;
		chdir("..");
        return;
    }
	// if the file is not in the Files directory throw error and return
	if (!file.fileOpen(fin, fileName))    {
        cout << "That file does not exist" << endl;
		chdir("..");
		return;
    }
	// collect all contents of the file
	string temp;
	while (fin.peek() != EOF) {
		temp += fin.get();
	}
    file.fileClose(fin);
	// store the encrypted file with a .enc extension
	string appendedFileName = fileName;
	appendedFileName += ".enc";
	crypter.lockAndStock(appendedFileName, temp);
	cout << "OK. The encrypted file is: " << fileName << ".enc" << endl;
	chdir("..");
}


// A file must be in the users private directory called Files in order for the 
// function to detect the correct file.
void menuHandler::decryptAfile(){
	// if the individual users Files directory does not exist, create it
	// reguardless, move into it
	if (chdir("Files") != 0)	{
		mkdir("Files", 999);
		chdir("Files");
	}
	cout << "Enter a file name: " << endl;
	string fileName;
	cin >> fileName;
	if (file.stringNull(fileName))    {
        cout << "The File cannot be empty" << endl;
		// if the filename is an empty string return to menu
		chdir("..");
        return;
    }
	if (!file.fileOpen(fin, fileName))    {
        cout << "That file does not exist" << endl;
		// if the file dosnt exist return to menu
		chdir("..");
		return;
    }
	file.fileClose(fin);
	string unAppendedFileName = fileName;
	// create a new fileName without a .enc extension for the decrypted file
	string strToSeek = ".enc";
	char * realFileName = new char[fileName.size()];
	
	for (int i = 0; i < fileName.size(); i++) {
		realFileName[i] = fileName.at(i);
	}
	
	if (strstr(realFileName, ".enc"))	{
		char * newFileName = new char[(sizeof realFileName) -4];
		
		for (int i = 0; i < fileName.size() - 4; i++) {
			newFileName[i] = realFileName[i];
		}
		//store the decrypted data in the new file without a .enc extension
		string temp = crypter.loadAndDecode(fileName);
		file.fileOpen(fout, newFileName);
		int i = 0;
		while (i < temp.size()) {
			fout << temp.at(i);
			i++;
		}
		file.fileClose(fout);
		cout << "OK. The decrypted file is: " << newFileName << endl;
		// decrypt successful, return
		chdir("..");
	}
	else {
		// the file dosnt have a .enc so therefore is not encrypted
		cout << "that file isn't encrypted " << endl;
		chdir("..");
		return;
	}

}

// function removes a record located in the individual users Records directory.
// no return type, if process failed throw an error to the screen.
void menuHandler::deleteRecord()	{
	// if the individual users Records directory does not exist, create it
	// reguardless, move into it
	if (chdir("Records") != 0)	{
		mkdir("Records", 999);
		chdir("Records");
	}
	string record;
    cout << "Enter the name of the record:" << endl;
	file.flushinput(cin);
	while (cin.peek() != '\n') {
		record += cin.get();
	}
	// collect the name of the record to remove... if it is empty or dosnt exist 
	// throw error
	if (file.stringNull(record)) {
		cout << "The Record cannot be empty" << endl;
		chdir("..");
        return;
	}
	if (!file.fileOpen(fin, record))    {
        cout << "That file does not exist" << endl;
		chdir("..");
		return;
    }
	file.fileClose(fin);
	// remove the file and return the status of how successful the operation was
	char * cstringRec = new char [record.size()];
	cstringRec = (char *)record.data();
	if(remove(cstringRec) == -1)
	{
		cout << record << " failed to delete" << endl;
		chdir("..");
		return;
	}
	else {
    cout << record << " was successfully deleted" << endl;
		chdir("..");
	return;
	}
	// finally return to the menu and normal directory
}

