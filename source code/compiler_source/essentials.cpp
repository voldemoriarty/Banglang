#include "essentials.h"
#define NL "\n"
//NOTE TO SELF:
//	asmgen_arith() and asmgen_str() process output strings only.  (ldloc_s, ldloc_n, num, str)
//	asmgen_handles() is supposed to sugar-coat the above two.

vector <string> SplitAtSpace(string s) {		//Volatile and Effective. Handle with Care
	vector <string> vec;
	bool inWord = false;
	int length = s.length();

	//Handle empty space
	if (s == "") {
		vec.push_back("");
		return vec;
	}

	for (int i = 0; i < length; i++) {
		if (s[i] == ' ' || s[i] == '\t') {
			inWord = false;
			continue;
		}
		else if (s[i] == '\"') {		//add escape character for quotes here.
			vec.push_back("");
			for (int j = i+1; j < length; j++) {
				if (s[j] == '\"') {
					inWord = false;		//force false: else will handle the next word.
					i = j;
					break;
				}
				else {
					vec[vec.size() - 1] += s.substr(j, 1);
				}
			}
			if (!inWord) {
				continue;
			}
		}
		else {
			if (!inWord) {
				vec.push_back("");
				inWord = true;
			}
			vec[vec.size() - 1] += s.substr(i, 1);
		}
	}
	return vec;
}

void trimEnds(string &s) {
	if (s.empty()) {
		return;
	}
	while (isspace(s[0])) {
		s = s.substr(1);
	}
	while (isspace(s[s.length() - 1])) {
		s = s.substr(0, s.length() - 1);
	}
}

void asmgen_str(string &str) {
	if (str[0] == '#') {		//i.e: SET #1 AS #0
		str = "ldloc_s " + str.substr(1);
	}
	else { //i.e: SET #1 AS "Hello Darkness my old friend"
		str = "str " + str + ";";
	}
	str += NL;
}

void toEquivalent::Continue(string &c) {
	if (c == "=") {
		c = "ceq";
	}
	else if (c == "<") {
		c = "cl";
	}
	else if (c == ">") {
		c = "cg";
	}
	else if (c == "<=") {
		c = "cle";
	}
	else if (c == ">=") {
		c = "cge";
	}
	else if (c == "!=") {
		c = "cne";
	}
}

void toEquivalent::Jump(string &c) {
	if (c == "=") {
		c = "jeq";
	}
	else if (c == "<") {
		c = "jl";
	}
	else if (c == ">") {
		c = "jg";
	}
	else if (c == "<=") {
		c = "jle";
	}
	else if (c == ">=") {
		c = "jge";
	}
	else if (c == "!=") {
		c = "jne";
	}
}

void toEquivalent::UpperString(string &inpStr) {
	int length = inpStr.length();
	for (unsigned int i = 0; i < length; i++) {
		if (inpStr[i] == '\"') {
			while (inpStr[++i] != '\"');
		}
		else if (isalpha(inpStr[i])) {
			inpStr[i] = toupper(inpStr[i]);
		}
	}
}