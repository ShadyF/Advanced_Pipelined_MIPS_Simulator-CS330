#ifndef CPU_H
#define CPU_H

#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "Memory.h"
#include "WBack.h"
#include "Parser.h"
class CPU
{
private:
	//std::vector<int> Fetch_buffer, Decode_buffer, Execute_buffer, Memory_buffer;
	std::vector<int> FTemp, DTemp, ETemp, MTemp;
	vector<int> FU_Mem;
	vector<int> FU_WB;
	bool* stall;

public:
	std::vector<int>* Regs;
	std::vector<int>* DataMemory;
	std::vector<int> InsMemory;
	std::vector<int> Fetch_buffer, Decode_buffer, Execute_buffer, Memory_buffer;
	int clock;

	Fetch FetchStage;
	Decode DecodeStage;
	Execute ExecuteStage;
	Memory MemoryStage;
	WBack WBStage;
	Parser Parse;

	CPU(); 				//should take text file here
	~CPU();
	void init(std::string filename);
	void run_one_cycle();
	void rst();

};
#endif
