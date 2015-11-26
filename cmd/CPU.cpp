#include <vector>
#include <fstream>
#include "Fetch.h"
#include "Parser.h"
#include "CPU.h"

CPU::CPU(std::string filename)
{
	Parser Parse;
  DataMemory = new vector<int>;
  Regs = new vector<int>;
  DataMemory->resize(32);
  Regs->resize(16);
	InsMemory = Parse.run(filename);
	FetchStage.init(InsMemory);
  DecodeStage.init(Regs);
  MemoryStage.init(DataMemory);
  WBStage.init(Regs);
	clock = 0;
  Execute_buffer.resize(9);
  Memory_buffer.resize(5);
  Fetch_buffer.resize(2);
  Decode_buffer.resize(16);
}

CPU::~CPU()
{

}

void CPU::run_one_cycle()
{
  vector<int> FU_Mem;
  vector<int> FU_WB;
  FU_Mem = MemoryStage.Send_FU_Mem_To_Execute(Execute_buffer);
  FU_WB = WBStage.Send_FU_WB_To_Execute(Memory_buffer);

  FTemp = FetchStage.run(0, 0);
  DTemp = DecodeStage.run(Fetch_buffer);
  ETemp = ExecuteStage.run(Decode_buffer, FU_Mem, FU_WB);
  MTemp = MemoryStage.Memory_run(Execute_buffer);
  WBStage.WB_run(Memory_buffer);

  Fetch_buffer = FTemp;
  Decode_buffer = DTemp;
  Execute_buffer = ETemp;
  Memory_buffer = MTemp;
  clock++;
}

void CPU::rst()
{
	//set fetch PC to 0
	//set regs to 0
	//set clock to 0
}
