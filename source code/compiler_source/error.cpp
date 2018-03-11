#include "error.h"
int error::lineNumber = 0;
bool error::hasErred = false;

error::error(string type) {
	bool hasErred = true;
	errorString = "\nError found in " + type + " statement\n"
		"Probable Line of Error: " + to_string(lineNumber) + NL;
	cerr << TAB << "===ERROR===" << endl << errorString;
	cin.get();
	exit(1);
}

error::error(string type, string addendum) {
	cerr << TAB << "===ERROR===" << endl << addendum << type << endl
		<< "Probable line of Error: " << lineNumber << endl;
	cin.get();
	exit(1);
}