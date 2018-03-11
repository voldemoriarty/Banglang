#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "map.h"

using namespace std;

class line {
private:
public:
	vector <string> vec;
	vector <string> SplitAtSpace(string);
	line(string);
	~line();
	void printVectorContents();
	void replace(string, string);
	void replaceAll(map[], int);
	string toString();
};