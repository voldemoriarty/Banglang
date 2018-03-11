#include "vm.h"
#include <cmath>

template<class T>
T stkpop(std::stack<T>& stk)
{
	if (stk.empty()) throw "Empty stack cannot be popped";
	T temp = stk.top();
	stk.pop();
	return temp;
}

template<class T>
void stkpush(std::stack<T>& stk, T val)
{
	stk.push(val);
}

template<class T>
void assign(std::vector<T>& ram, T val, size_t index)
{
	if (index == ram.size()) ram.push_back(val);
	else if (index < ram.size()) ram.at(index) = val;
	else throw "Dont waste memory!";
}


std::map<std::string, size_t> labels;
std::map<std::string, size_t> funcs;

VM::VM(std::string file):Source(file) {}

VM::VM(std::vector<std::string>& instr) : Source(instr) {}

VM::VM(){}

std::vector<std::string> keyws = {
	/*		These manage memory	*/
	"stloc_n",
	"ldloc_n",
	"stloc_s",
	"ldloc_s",
	/*		These manage maths  */
	"add",
	"sub",
	"mul",
	"div",
	"exp",
	"rem",
	/*		These manage jumping	*/
	"label",
	"gonna",
	/*		These manage comparisons	 */
	"jmp",
	"jeq",
	"jle",
	"jge",
	"jne",
	"jl",
	"jg",
	"jeq_str",
	/*		These manage IO		*/
	"out_s",
	"in_s",
	"out_n",
	"in_n",
	/*      These manage declarations	*/
	"num",
	"str",
	/*		These manage functions		*/
	"func",
	"call",
	"ret",
	"end",
	/*     On choice of asad */
	"ceq",
	"cne",
	"cle",
	"cg",
	"cl",
	"cge",
	"ceq_str",

	"wait",

	"nl",

	"exit"
};

void VM::runFile()
{
	bool infunc = false;
	std::stack<size_t> offset_s;
	std::stack<size_t> offset_n;
	std::stack<size_t> returns;
	offset_n.push(0);
	offset_s.push(0);
	for (size_t i = 0; i < instr.size(); i++) {
		try {
			/* Loop through all instructions in instr */
			std::string temp = instr[i];
			if (instr[i].find_first_not_of(" \n\t\r") == std::string::npos) continue;
			/*  Trim Left  */
			temp = temp.substr(temp.find_first_not_of(" \n\t\r"));
			/*  Trim Right */
			temp = temp.substr(0, temp.find_last_not_of(" \n\t\r") + 1);
			/*  Ignore commented lines   */
			if (temp[0] == comment_char) continue;
			/*  Ignore the inline comments  */
			temp = temp.substr(0, temp.find_first_of(comment_char));
			/*  Now it is formatted  */
			std::stringstream ss(temp);
			std::string temp2;
			std::string arg;

			ss >> temp2;
			ss.get();
			if (getKeyWord(temp2) == keyws_t::label) {
				ss >> arg;
				labels[arg] = i;
			}
		}
		catch (char* msg) {
			std::cerr << msg << std::endl
				<< "Error occured during execution of line " << i + 1 << std::endl;
			break;
		}
		catch (...) {
			std::cerr << "Error ocurred during execution of line " << i + 1 << std::endl;
			break;
		}
	}
	for (size_t i = 0; i < instr.size(); i++) {
		/* Loop through all instructions in instr */
		try {
			std::string temp = instr[i];
			keyws_t keyWord;
			if (instr[i].find_first_not_of(" \n\t\r") == std::string::npos) continue;
			/*  Trim Left  */
			temp = temp.substr(temp.find_first_not_of(" \n\t\r"));
			///*  Trim Right */
			//temp = temp.substr(0, temp.find_last_not_of(" \n\t\r") + 1);
			/*  Ignore commented lines   */
			if (temp[0] == comment_char) continue;
			/*  Ignore the inline comments  */
			temp = temp.substr(0, temp.find_last_of(comment_char));
			/*  Now it is formatted  */
			std::stringstream ss(temp);
			std::string temp2;
			std::string arg;

			ss >> temp2;
			ss.get();
			std::getline(ss, arg);
			keyWord = getKeyWord(temp2);
			if (keyWord != keyws_t::str) {
				try {
					arg = arg.substr(arg.find_first_not_of(" \t\n\r"));
					arg = arg.substr(0, arg.find_last_not_of(" \t\n\r") + 1);
				}
				catch (...) {}	//exception will be caught if arg is whitespace
			}
			if (infunc && keyWord != keyws_t::end) continue;
			double numTemp;
			/* The Circuits Begin Here; Enter with Brain and Caution.*/
			switch (keyWord) {
			case keyws_t::Count:
				throw "Keyword not found";
				break;
			case keyws_t::stloc_n:
				assign(n_ram, stkpop(n_stk), std::stoi(arg) + offset_n.top());
				break;
			case keyws_t::ldloc_n:
				stkpush(n_stk, n_ram.at(std::stoi(arg) + offset_n.top()));
				break;
			case keyws_t::stloc_s:
				assign(s_ram, stkpop(s_stk), std::stoi(arg) + offset_s.top());
				break;
			case keyws_t::ldloc_s:
				stkpush(s_stk, s_ram[std::stoi(arg) + offset_s.top()]);
				break;
			case keyws_t::add:
				stkpush(n_stk, stkpop(n_stk) + stkpop(n_stk));
				break;
			case keyws_t::sub:
				numTemp = stkpop(n_stk);
				stkpush(n_stk, stkpop(n_stk) - numTemp);
				break;
			case keyws_t::mul:
				stkpush(n_stk, stkpop(n_stk) * stkpop(n_stk));
				break;
			case keyws_t::div:
				numTemp = stkpop(n_stk);
				stkpush(n_stk, stkpop(n_stk) / numTemp);
				break;
			case keyws_t::exp:
				numTemp = stkpop(n_stk);
				stkpush(n_stk, pow(stkpop(n_stk), numTemp));
				break;
			case keyws_t::label:
				labels[arg] = i;
				break;
			case keyws_t::gonna:
				i = std::stoi(arg) - 2;
				break;
			case keyws_t::out_n:
				std::cout << stkpop(n_stk);
				break;
			case keyws_t::in_n:
#ifdef _WIN32
				_flushall();
#endif
				std::cin >> temp;
				stkpush(n_stk, std::stod(temp));
				break;
			case keyws_t::out_s:
				std::cout << stkpop(s_stk);
				break;
			case keyws_t::in_s:
				temp.clear();
				std::getline(std::cin, temp);
				stkpush(s_stk, temp);
				break;
			case keyws_t::jmp:
				i = labels[arg];
				break;
			case keyws_t::ceq:
				if (!(stkpop(n_stk) == stkpop(n_stk)))
					i = labels[arg];
				break;
			case keyws_t::cne:
				if (!(stkpop(n_stk) != stkpop(n_stk)))
					i = labels[arg];
				break;
			case keyws_t::cle:
				numTemp = stkpop(n_stk);
				if (!(stkpop(n_stk) <= numTemp))
					i = labels[arg];
				break;
			case keyws_t::cg:
				numTemp = stkpop(n_stk);
				if (!(stkpop(n_stk) > numTemp)) 
					i = labels[arg];
				break;
			case keyws_t::cl:
				numTemp = stkpop(n_stk);
				if (!(stkpop(n_stk) < numTemp)) 
					i = labels[arg];
				break;
			case keyws_t::cge:
				numTemp = stkpop(n_stk);
				if (!(stkpop(n_stk) >= numTemp)) 
					i = labels[arg];
				break;
			case keyws_t::ceq_str:
				if (!(stkpop(s_stk) == stkpop(s_stk)))
					i = labels[arg];
				break;
			case keyws_t::jeq:
				if (stkpop(n_stk) == stkpop(n_stk))
					i = labels[arg];
				break;
			case keyws_t::jle:
				numTemp = stkpop(n_stk);
				if (stkpop(n_stk) <= numTemp) i = labels[arg];
				break;
			case keyws_t::jl:
				numTemp = stkpop(n_stk);
				if (stkpop(n_stk) < numTemp) i = labels[arg];
				break;
			case keyws_t::jge:
				numTemp = stkpop(n_stk);
				if (stkpop(n_stk) >= numTemp) i = labels[arg];
				break;
			case keyws_t::jg:
				numTemp = stkpop(n_stk);
				if (stkpop(n_stk) > numTemp) i = labels[arg];
				break;
			case keyws_t::jne:
				if (stkpop(n_stk) != stkpop(n_stk))
					i = labels[arg];
				break;
			case keyws_t::jeq_str:
				if (stkpop(s_stk) == stkpop(s_stk))
					i = labels[arg];
				break;
			case keyws_t::num:
				stkpush(n_stk, std::stod(arg));
				break;
			case keyws_t::str:
				stkpush(s_stk, arg);
				break;
			case keyws_t::rem:
				numTemp = stkpop(n_stk);
				stkpush(n_stk, (double)((int)stkpop(n_stk) % (int)numTemp));
				break;
			case keyws_t::exit:
				return;
				break;
			case keyws_t::func:
				infunc = true;
				funcs[arg] = i;
				break;
			case keyws_t::ret:
				i = returns.top();
				returns.pop();
				offset_n.pop();
				offset_s.pop();
				break;
			case keyws_t::call:
				returns.push(i);
				offset_n.push(n_ram.size());
				offset_s.push(s_ram.size());
				i = funcs[arg];
				break;
			case keyws_t::end:
				infunc = false;
				break;
			case keyws_t::wait:
				std::cin.get();
				break;
			case keyws_t::nl:
				std::cout << std::endl;
				break;
				/*The Circuits End Here*/
			}
		}
		catch (char* msg) {
			std::cerr << msg << std::endl << "Error ocurred during execution of line " << i + 1 << std::endl;
			exit(1);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << "\n At line " << i + 1 << std::endl;
			exit(1);
		}
		catch (...) {
			std::cerr << "Error occured during execution of line " << i + 1 << std::endl;
			exit(1);
		}
	}
}

keyws_t getKeyWord(std::string kw) {
	for (unsigned int i = 0; i < keyws.size(); i++) {
		if (keyws[i] == kw) return static_cast<keyws_t>(i);
	}
	return keyws_t::Count;
}
