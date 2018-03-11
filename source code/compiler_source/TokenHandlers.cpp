#include "TokenHandlers.h"
//Implement file page class

using namespace std;

int ifBlockCounter = 0;
int whileBlockCounter = 0;
int doWhileBlockCounter = 0;

extern ifstream fin;

void setHandle(vector <string> &vec) {		//Operational.
	if (vec.size() != 3) {
		error Error("SET");
	}
	vec.erase(vec.begin() + 1);
	string stlocType = "stloc_n ";

	if (vec[0][0] == '$') {
		if (vec[1][0] == '-') {
			error Error("Precede a negative number with 0. Refer to Documentation.", "in SET\n");
		}
		asmgen_arith(vec[1]);
	}
	else {
		asmgen_str(vec[1]);
		stlocType = "stloc_s ";
	}

	vec[0] = stlocType + vec[0].substr(1);
	vec[1] += vec[0];
	vec.erase(vec.begin());	//Nice hack
}

void printHandle(vector <string> &vec) {	//Operational.
	if (vec.size() != 1) {
		error Error("PRINT");
		return;
	}
	if (vec[0][0] == '#' || (!isdigit(vec[0][0]) && vec[0][0] != '(' && vec[0][0] != '$')){
		asmgen_str(vec[0]);
		vec[0] += "out_s";
	}
	else {
		asmgen_arith(vec[0]);
		vec[0] += "out_n";
	}
}

void inputHandle(vector <string> &vec) {	//operational
	if (vec.size() != 1) {
		error Error("INPUT");
		return;
	}
	if (vec[0][0] == '$')
		vec[0] = "\nin_n\nstloc_n " + vec[0].substr(1);
	else if (vec[0][0] == '#')
		vec[0] = "\nin_s\nstloc_s " + vec[0].substr(1);
}

void ifHandle(vector <string> &vec) {		//Operational
	if (vec.size() != 4) {
		error Error("IF");
		return;
	}
	string blockNumber = to_string(++ifBlockCounter);
	if (vec.size() != 4) {
		cout << "\nError in if statement. You are probably missing a then.\n";
		return;
	}
	vec.erase(vec.begin() + vec.size() - 1);		///Removes THEN
	if (isalpha(vec[0][0]) || vec[0][0] == '#') {
		asmgen_str(vec[0]);
		asmgen_str(vec[2]);
		vec[1] = "ceq_str ";
	}
	else {
		asmgen_arith(vec[0]);
		asmgen_arith(vec[2]);
		toEquivalent::Continue(vec[1]);
	}
	vec[1] += " ELSE" + blockNumber;	//deals with jump to
	vec[0].append(vec[2]);
	vec[0].append(vec[1]);
	vec.erase(vec.begin() + 1);
	vec.erase(vec.begin() + 1);
	//First line of IF is processed. Hijack stream now//
	string buffer;
	bool elseExists = false;
	while (getline(fin, buffer)) {
		trimEnds(buffer);
		if (buffer == "ELSE") {
			vec[0] += NL "jmp ENDIF" + blockNumber;
			vec[0] += NL "label ELSE" + blockNumber;
			elseExists = true;
		}
		else if (buffer == "ENDIF") {
			if (!elseExists)
				vec[0] += NL "label ELSE" + blockNumber;
			vec[0] += NL "label ENDIF" + blockNumber;
			break;
		}
		else {
			asmgen_handles(buffer, vec[0]);
		}
	}
}

void whileHandle(vector <string> &vec) {	//OOPify and Cleanup.
	string header, buffer;
	if (vec.size() != 3) {
		error Error("WHILE");
		return;
	}
	if (isalpha(vec[0][0]) || vec[0][0] == '#') {
		asmgen_str(vec[0]);
		asmgen_str(vec[2]);
		vec[1] = "ceq_str ";
	}
	else {
		asmgen_arith(vec[0]);
		asmgen_arith(vec[2]);
		toEquivalent::Continue(vec[1]);
	}

	string blockNumber = to_string(++whileBlockCounter);		//whileBlockCounter is global. That's why.
	vec[0] = "label WHILEBLC" + blockNumber + NL + vec[0] + vec[2] + vec[1] + " WEND" + blockNumber + NL;		//ceq WEND1 etc
	string postHeader = "";

	while (getline(fin, buffer)) {	//stream highJack begins
		trimEnds(buffer);
		if (buffer == "WEND")
			break;
		else 
			asmgen_handles(buffer, postHeader);
	}

	vec[0] += postHeader + "jmp WHILEBLC" + blockNumber + NL + "label WEND" + blockNumber;
	vec.erase(vec.begin() + 1);
	vec.erase(vec.begin() + 1);
}

void doWhileHandle(vector <string> &vec) {
	string header, buffer;
	if (vec.size() != 3) {
		error Error("Do-While");
		return;
	}
	if (isalpha(vec[0][0]) || vec[0][0] == '#') {
		asmgen_str(vec[0]);
		asmgen_str(vec[2]);
		vec[1] = "jeq_str ";
	}
	else {
		asmgen_arith(vec[0]);
		asmgen_arith(vec[2]);
		toEquivalent::Jump(vec[1]);
	}

	string blockNumber = to_string(++doWhileBlockCounter);		//doWhileBlockCounter is global. That's why.
	header = "label DWHILEBLC" + blockNumber + NL;
	string postHeader = "";

	while (getline(fin, buffer)) {	//stream highJack begins
		trimEnds(buffer);
		if (buffer == "DWEND")
			break;
		else
			asmgen_handles(buffer, postHeader);
	}
	header += postHeader + vec[0] + vec[2] + vec[1] + " DWHILEBLC" + blockNumber + NL;
	vec[0] = header;
	vec.erase(vec.begin() + 1);
	vec.erase(vec.begin() + 1);
}

void printlHandle(vector<string> &vec) {
	if (vec.size() != 1) {
		error Error("PRINTL");
		return;
	}
	printHandle(vec);
	vec[0].append("\nnl");
}

void asmgen_handles(string argStr, string &output) {
	++error::lineNumber;
	vector <string> vec = SplitAtSpace(argStr);
	string firstToken = vec[0];
	vec.erase(vec.begin());

	if (firstToken == "SET") {
		setHandle(vec);
	}
	else if (firstToken == "PRINT") {
		printHandle(vec);
	}
	else if (firstToken == "INPUT") {
		inputHandle(vec);
	}
	else if (firstToken == "IF") {
		ifHandle(vec);
	}
	else if (firstToken == "WHILE") {
		whileHandle(vec);
	}
	else if (firstToken == "PRINTL") {
		printlHandle(vec);
	}
	else if (firstToken == "DOWHILE") {
		doWhileHandle(vec);
	}
	else if (firstToken == "COM" || firstToken == "//") {		//Comment Handle
		return;
	}
	else if(firstToken != ""){
		error(firstToken, "KeyWord not found. Found instead: ");
		return;
	}

	vec[0].append(NL);
	output += NL + vec[0];
}
