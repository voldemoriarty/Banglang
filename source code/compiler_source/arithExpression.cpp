#include "arithExpression.h"
#define NL "\n"
using namespace std;

void vectorToAsm(vector <string>&);
void asmResolve(vector <string>&);
/*
R.H.S mathematical expression to assembly.
*/
vector <string> stringToVector(string str) {
	vector <string> vec;
	vec.push_back("");
	int len = str.size();
	// Very simple algorithm. Put digits (and parens) into a vector element. If a non-digit is encountered:
	// Start a new entry. Put the non-digit into the new entry, and start a new entry for the expected numbers or parens that follow.
	for (unsigned int i = 0; i<str.length(); i++) {
		if (str[i] == ' ' || str[i] == '\t') {			//WhitespaceHandle
			continue;
		}
		else if (str[i] == '.' || isalnum(str[i]) || str[i] == '$') {		//NumberHandle
			vec[vec.size() - 1] += str[i];
		}
		else if (str[i] == '(') {	//paren Handle. No new entry is made for paren in this block. *1(Appendix)
			int j, parenCount = 1;
			//Only complex part of code. Mildly elegant solution to a problem created by grossly inelegant plan.
			//DESCRIPTION: this part picks the whole paren block.
			for (j = i+1; parenCount != 0 && j<=len; j++) {
				if (str[j] == '(') { parenCount++; }
				if (str[j] == ')') { parenCount--; }
			}
			j--; //Correcting for-loop's last offset;
			string newstr = str.substr(i+1, (j-i)-1);
			//DESCRITION: the following part treats paren block as a statement itself (through recursion).
			//...At the end, a single vector entry is produced with perfect asm of paren.
			vector <string> tempVec = stringToVector(newstr);
			vectorToAsm(tempVec);

			vec[vec.size() - 1] += tempVec[0];

			i = j;  //Continue from after the paren.
		}
		else {			//All_else Handle. Make a new entry and put the unhandled into it. Handles our operators.
				vec.push_back("");	//End by making yet another entry for expected numbers/variables/parens that follow.
				vec[vec.size() - 1] += str[i];
				vec.push_back("");
		}
	}
	return vec;
}

void asmResolve(vector <string> &vec) {
	for (unsigned int i = 0; i<vec.size(); i++) {
		if (vec[i] == "+") {
			vec[i] = "add";
		}
		else if (vec[i] == "-") {
			vec[i] = "sub";
		}
		else if (vec[i] == "*") {
			vec[i] = "mul";
		}
		else if (vec[i] == "/") {
			vec[i] = "div";
		}
		else if (vec[i] == "^") {
			vec[i] = "exp";
		}
		else if (vec[i] == "%") {
			vec[i] = "rem";
		}
		else if (isdigit(vec[i][0])) {
			vec[i] = "num "+vec[i];
		}
		else if (vec[i][0] == '$') {
			vec[i] = "ldloc_n " + vec[i].substr(1, 1);
		}
	}
}

void vectorToAsm(vector <string> &vec) {
	/*Very Simple Algorithm. In order of DMAS, concatenate vector entries (essentially individual strings).*/
	/*If a div is found, convert it into infinix. So on with the other symbols.*/
	bool operatorFlag;
	string symbol[6] = {"exp", "div", "mul", "rem", "add", "sub"};
	asmResolve(vec);

	int s = 0;
	while (s<6) {
		operatorFlag = 0;    //If a certain operator is not found at all in a run. Check for the next operator.
		for (unsigned int i = 0; i<vec.size(); i++) {
			if (vec[i] == symbol[s]) {
				vec[i - 1].append("\n");
				vec[i - 1].append(vec[i + 1] + "\n");
				vec[i - 1].append(vec[i]);
				vec.erase(vec.begin() + i);
				vec.erase(vec.begin() + i);
				operatorFlag = 1;
			}
		}
		if (!operatorFlag) { s++; }
	}
}

void asmgen_arith(string &str) {
	vector <string> vec;
	vec = stringToVector(str);	//Break string into vector of operators and operands.
	vectorToAsm(vec);	//Make assembly from the vector
	vec[0] += NL;
	str = vec[0];
}

//Appendix:
/*
*1 - All parens are supposed to be preceded by operators, paren blocks will aptly go into a fresh entry made by previous operator handles.
*/
