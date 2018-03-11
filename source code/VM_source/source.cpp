#include "source.h"

Source::Source(std::string file)
{
	std::string temp;
	std::ifstream fin(file, std::ios::in);
	if (!fin.is_open()) {
		std::cerr << "Could not open file:" << file << "! Make sure it exists\n";
	}
	while (std::getline(fin, temp)) {
		instr.push_back(temp);
		temp.clear();
	}
}

Source::Source(std::vector<std::string>& instrs)
{
	instr = instrs;
}

Source::Source()
{
}

std::string & Source::instrAt(size_t index)
{
	if (index >= instr.size()) std::cerr << "Cannot execute instr at index. Index out of range.\n";
	else return instr[index];
}
