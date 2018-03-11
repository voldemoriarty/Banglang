#pragma once
#ifndef SOURCE_H
#define SOURCE_h

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Source {
protected:
	std::vector<std::string> instr;		//container to store instructions
public:
	Source(std::string file);
	Source(std::vector<std::string>& instrs);
	Source();
	std::string& instrAt(size_t index);
};

#endif