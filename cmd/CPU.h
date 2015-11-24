#ifndef CPU_H
#define CPU_H

#include "Fetch.h"

class CPU
{
private:
	std::vector<int> Fetch_buffer, Decode_buffer, Execute_buffer, Memory_buffer, WB_buffer;
  Fetch FetchStage;

public:
	std::vector<int> Regs;
  std::vector<int> DataMemory;                      //to be implemented
	std::vector<int> InsMemory;
	int clock;
	
	CPU(std::string); 				//should take text file here
	~CPU();
	void run_one_cycle();
	void rst();

};
#endif
