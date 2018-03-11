#include "line.h"
#define IS_ARITH_OP (s[i] == '*' || s[i] == '-' || s[i] == '+' || s[i] == '/' || s[i] == '^' || s[i] == '%' || s[i] == '(' || s[i] == ')')
//May contain assertion error
vector <string> line::SplitAtSpace(string s) {		//Line's version of splitter.
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
			vec.push_back(s.substr(i, 1));		//saves the bloody white spaces.
			continue;
		}
		else if (s[i] == '\"') {		//add escape character for quotes here.
			vec.push_back("\"");
			for (int j = i + 1; j < length; j++) {
				if (s[j] == '\"') {
					inWord = false;		//force false: else will handle the next word.
					i = j;
					vec[vec.size() - 1] += "\"";
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
		else if (IS_ARITH_OP) {  //Arith_Expression Splitter follows
			vec.push_back(s.substr(i, 1));
			inWord = false;
			continue;
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

line::line(string s){
	SplitAtSpace(s);
	if (vec[0] == "DIM") {
		vec[0] = "SET";
		if (vec[6] == "NUMBER") {
			vec[6] = "0";
		}
		else if (vec[6] == "STRING") {
			vec[6] = "NULL";
		}
	}
}

void line::printVectorContents() {
	for (auto a : vec) {
		cout << a << endl;
	}
}

void line::replace(string token, string alias) {
	for (auto &a : vec) {
		if (a == token)
			a = alias;
	}
}

string line::toString() {
	string retStr = "";
	int size = vec.size();
	for (int i = 0; i < size; i++) {
		retStr.append(vec[i]);
	}
	return retStr;
}

void line::replaceAll(map switchMap[], int size) {
	//if (vec[0] == "DIM")
		//return;
	for (int i = 0; i <= size; i++) {
		replace(switchMap[i].token, switchMap[i].alias);
	}
}

line::~line() {
}