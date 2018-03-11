#include "defines.h"
#include "TokenHandlers.h"
#include "line.h"
#include <exception>
using namespace std;

ifstream fin;
ofstream fout;
string error;

int main(int argc, char* argv[]) {
	try {
		string source, destination;
		source = "bSource.txt";
		destination = "blabla";

		if (argc == 3) {
			source = argv[1];
			destination = argv[2];
		}
		else if (argc != 1) {
			cout << "Syntax: bang [fileName = \"bSource.txt\"] [output = \"blabla\"]";
			return 0;
		}

		cout << "\n==========Resolving Variables===========\n";
		//RESOLVE VARIABLES _ SUGAR FACTORY
		string buffer;
		mapList makeMapList(source);
		fin.open(source);
		fout.open("Source.o");

		while (getline(fin, buffer)) {
			if (buffer.empty()) {		//Handle Empty Strings: Do absolutely nothing about them
				continue;
			}
			trimEnds(buffer);
			toEquivalent::UpperString(buffer);
			line myLine(buffer);
			myLine.replaceAll(makeMapList.switchMap, mapList::length);
			string refVar = myLine.toString();
			cout << refVar << endl;
			fout << refVar << endl;
		}

		fout.close();
		fin.close();

		// GENERATE ASSEMBLY
		cout << "\n===========Generating Assembly===========\n";
		string output = "";

		fin.open("Source.o");
		fout.open(destination);

		while (getline(fin, buffer)) {
			asmgen_handles(buffer, output);
		}

		cout << output;
		fout << output << flush;
		fout.close();
		fin.close();
		return 0;
	}
	catch (exception& e) {
		cerr << "Exception caught: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "Exception caught: Unknown type\n";
		return 1;
	}
}

///				WORKING MAIN CONTENTS: SKELETON COMPILER
//vector <string> vec;
//string buffer;
//string output = "";
//
//fin.open("source.txt");
//fout.open("C:\\Users\\Asad\\Desktop\\Playground\\blabla");
//while (getline(fin, buffer)) {
//	asmgen_handles(buffer, output);
//}
//
//cout << output;
//fout << output << flush;
//cin.get();
//return 0;

///				WORKING MAIN CONTENTS: SKELETON SUGARCOATING
//string map[3][2] = { { "X", "$1" },{ "XTRA", "$2" },{ "apple", "$3" } };
//line myLine("IF X*3+5 = XTRA THEN");
//line("15*16");
//myLine.printVectorContents();
//myLine.replaceAll(map, 3);
//cout << myLine.toString();
//cin.get();
//return 0;