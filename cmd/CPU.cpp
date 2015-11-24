#include <vector>
#include <fstream>
#include "Fetch.h"
#include "Parser.h"
#include "CPU.h"

CPU::CPU(std::string filename)
{
  Parser Parse;
  InsMemory = Parse.run(filename);
  FetchStage.init(InsMemory);
	clock = 0;
	Regs.resize(16);
}

CPU::~CPU()
{
	
}

void CPU::run_one_cycle()
{
	
}

void CPU::rst()
{
	//set fetch PC to 0
	//set regs to 0
	//set clock to 0
	
}
