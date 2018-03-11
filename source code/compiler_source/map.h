#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "essentials.h"
#define MAX 1000
class map {
private:
	static int stringAliasCount;
	static int numberAliasCount;
public:
	string token;
	string alias;
	map();
	void set(string, string);
};

class mapList {
public:
	ifstream finL;
	static int length;
	map switchMap[MAX];
	mapList(string&);
};