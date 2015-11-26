#ifndef CPU_H
#define CPU_H

#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "Memory.h"
#include "WBack.h"

class CPU
{
private:
	std::vector<int> Fetch_buffer, Decode_buffer, Execute_buffer, Memory_buffer;
  std::vector<int> FTemp, DTemp, ETemp, MTemp;
  Fetch FetchStage;
  Decode DecodeStage;
  Execute ExecuteStage;
  Memory MemoryStage;
  WBack WBStage;


public:
	std::vector<int>* Regs;
  std::vector<int>* DataMemory;
	std::vector<int> InsMemory;

	int clock;
	
	CPU(std::string); 				//should take text file here
	~CPU();
	void run_one_cycle();
	void rst();

};
#endif
