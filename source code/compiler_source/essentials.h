#pragma once
#include <vector>
#include <string>
#include <cctype>

using namespace std;

vector <string> SplitAtSpace(string);
void asmgen_str(string &);
void trimEnds(string&);

class toEquivalent {
public:
	static void Jump(string&);
	static void Continue(string&);
	static void UpperString(string&);
};