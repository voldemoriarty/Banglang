#pragma once
#include "defines.h"
#include "error.h"

#define NL "\n"

void asmgen_handles(string, string&);

void setHandle(vector <string> &vec);
void printHandle(vector <string> &vec);
void printlHandle(vector <string> &vec);
void inputHandle(vector <string> &vec);
void whileHandle(vector <string> &vec);
void ifHandle(vector <string> &vec);
void doWhileHandle(vector <string> &vec);