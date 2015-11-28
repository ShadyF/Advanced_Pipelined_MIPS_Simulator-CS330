#include <vector>
#include <fstream>
#include "Fetch.h"
#include "Parser.h"
#include "CPU.h"

CPU::CPU(std::string filename)
{
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
  Execute_buffer.resize(10);
  Memory_buffer.resize(6);
  Fetch_buffer.resize(2);
  Decode_buffer.resize(17);
  Execute_buffer[9] = -1;
  Memory_buffer[5] = -1;
  Fetch_buffer[0] = -1;
  Decode_buffer[16] = -1;
  FU_Mem.resize(4);
  FU_WB.resize(4);
}

CPU::~CPU()
{

}

void CPU::run_one_cycle()
{
  FU_Mem = MemoryStage.Send_FU_Mem_To_Execute(Execute_buffer);
  FU_WB = WBStage.Send_FU_WB_To_Execute(Memory_buffer);
  FTemp = FetchStage.run(0, 0, Decode_buffer[14], Decode_buffer[15]);
  ETemp = ExecuteStage.run(Decode_buffer, FU_Mem, FU_WB);
  MTemp = MemoryStage.Memory_run(Execute_buffer, FU_Mem);
  WBStage.WB_run(Memory_buffer);                                    //write in first half
  DTemp = DecodeStage.run(Fetch_buffer);                            //read in second half
  clock++;
  if(DTemp[14] == 1) //if j
  {
    Fetch_buffer[0] = -1;
    Decode_buffer[14] = DTemp[14];
    Decode_buffer[15] = DTemp[15];
    return;
  }
  else if (ExecuteStage.stall == 1)
  {
      Execute_buffer[9] = -1;
      Memory_buffer = MTemp;
      return;
  }
  Fetch_buffer = FTemp;
  Decode_buffer = DTemp;
  Execute_buffer = ETemp;
  Memory_buffer = MTemp;

}

void CPU::rst()
{
	//set fetch PC to 0
	//set regs to 0
	//set clock to 0
}