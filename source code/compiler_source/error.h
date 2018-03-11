#pragma once
#include <string>
#include <iostream>
#define NL "\n"
#define TAB "\t"

using namespace std;

class error {
public:
	static int lineNumber;
	static bool hasErred;
	string errorString;
	error(string);
	error(string, string);
};