#include "memory.h"

void Memory::clearMem()
{
	std::vector<double> d = {};
	n_ram.swap(d);
	std::vector<std::string> s = {};
	s_ram.swap(s);
	std::stack<double> ds = {};
	std::stack<std::string> ss = {};
	s_stk.swap(ss);
	n_stk.swap(ds);
}
