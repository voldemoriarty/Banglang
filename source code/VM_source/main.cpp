/*

@Author: Saad

--Note--
VM is desgined for C++11. Older Compilers may not support it.
--endNote--

Main entry point for the VM 
VM interprets each line from the source assembly and executes it

*/

#include "vm.h"

int main(int argc, char* argv[]) {
	std::string fileName;
	if (argc > 1) {
		if (static_cast<std::string>(argv[1]) == static_cast<std::string>("help")) {
			std::cout << "Usage: " << argv[0] << " [source file name]\n";
			return 0;
		}
		fileName = argv[1];
	}
	else
		fileName = "bootloader";
	VM v(fileName);
	v.runFile();
	return 0;
}