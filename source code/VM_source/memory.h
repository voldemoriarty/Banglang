#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <stack>
#include <string>

#define vector_s std::vector<std::string>
#define vector_n std::vector<double>
#define stack_s std::stack<std::string>
#define stack_n std::stack<double>

class Memory {
public:
	vector_s s_ram;
	vector_n n_ram;
	stack_s  s_stk;
	stack_n  n_stk;
	void clearMem();
	
};

#endif

