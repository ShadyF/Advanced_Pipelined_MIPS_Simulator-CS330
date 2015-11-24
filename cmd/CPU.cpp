#include "CPU.h"

CPU::CPU()
{
	//get from parset and input to inst_mem vector
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
