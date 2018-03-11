#pragma once
#ifndef VM_H
#define VM_H

#include "memory.h"
#include "source.h"
#include "semantics.h"
#include <sstream>
#include <iostream>
#include <exception>


class VM : public Memory, public Source {
public:
	VM(std::string file);
	VM(std::vector<std::string>& instr);
	VM();
	void runFile();
};

keyws_t getKeyWord(std::string kw);

#endif