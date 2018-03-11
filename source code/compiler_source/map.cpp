#include "map.h"

using namespace std;

int map::stringAliasCount = -1;
int map::numberAliasCount = -1;
int mapList::length = -1;

map::map(){}

void map::set(string token, string type){
	if (type == "STRING") {
		alias = "#" + to_string(++stringAliasCount);
		map::token = token;
	}
	else if (type == "NUMBER") {
		alias = "$" + to_string(++numberAliasCount);
		map::token = token;
	}
}

mapList::mapList(string& source) {
	finL.open(source);
	string buffer;
	while (getline(finL, buffer)) {
		trimEnds(buffer);
		if (buffer.empty()) {
			continue;
		}
		toEquivalent::UpperString(buffer);
		vector <string> vec = SplitAtSpace(buffer); //The general splitter from essentials.h. Used to figure dims
		if (vec[0] == "DIM") {
			switchMap[++length].set(vec[1], vec[3]);
		}
	}
	finL.close();
}