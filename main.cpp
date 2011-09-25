#include "menuhandler.h"


// menuHandler handles to bulk of my code 
int main (int argc, char *argv[])
{
	//If the main directory 'Resources' does not exist
	// create it. reguardless move into it
	// call the menuHandler, sit back and once
	// execution is finished return to the native directory
	// and exit
	if (chdir("Resources") != 0)	{
		mkdir("Resources", 999);
		chdir("Resources");
	}
	menuHandler();
	chdir("..");
    return 0;
}
