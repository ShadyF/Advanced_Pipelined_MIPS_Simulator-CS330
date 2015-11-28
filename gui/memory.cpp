#include <vector>
#include <exception>
#include <iostream>
#include "Memory.h"

using namespace std;
Memory::Memory()
{}

void Memory::init(vector<int>* CPU_DataMemory)
{
  DataMemory = CPU_DataMemory;
        Memory_Buffer.resize(6);
        Mem_Forwarding_Unit.resize(4);
};

//Brach to be implemented
vector<int> Memory::Memory_run(vector <int> IExecute_Buffer, vector<int> FU_WB)
{
  pc = IExecute_Buffer[9];
  if(pc < 0)
  {
      vector<int> temp(6);
      temp[5] = -1;
      return temp;
  }
        // Extracting IExecute Buffer.
        int RegWrite = IExecute_Buffer[0],
                MemToReg = IExecute_Buffer[1],
                //^WB
                Branch = IExecute_Buffer[2],
                MemRead = IExecute_Buffer[3],
                MemWrite = IExecute_Buffer[4],
                Zero = IExecute_Buffer[5],
                ALU_Result = IExecute_Buffer[6],
                RT_or_RD = IExecute_Buffer[7],
                R2 = IExecute_Buffer[8];		//New part of buffer from Shady (R2 to store in Data Memory)
        int Mem_Data = -3;



	//Nothing for Zero yet.
	if (RegWrite && MemWrite)
		cout << "Writing to both memory and regs" <<endl;

	if (MemRead && MemWrite)	//if zizo
		cout << "zizo, read and write" <<endl;

	if (FU_WB[0] && ALU_Result == FU_WB[3])
			R2 = FU_WB[2];

	if (MemRead && !MemWrite)		//Memory Read is ON
	{
		if (ALU_Result < 0 || ALU_Result > 32)
			Mem_Data = -1;			//out of range
		else
			Mem_Data = DataMemory->at(ALU_Result);
	}

	if (MemWrite && !MemRead)		//Memory Write is ON
	{
		if (ALU_Result < 0 || ALU_Result > 32)
			cout << "Out of range @ Memory" <<endl;
		else
			DataMemory->at(ALU_Result) = R2;
	}
	//Memory_Buffer.resize(5);		//Size of buffer for WB Stage
	//Creating Memory_Buffer
	Memory_Buffer[0] = RegWrite;		//0
	Memory_Buffer[1] = MemToReg;		//1
											//^ WB
	Memory_Buffer[2] = Mem_Data;		//2
	Memory_Buffer[3] = ALU_Result;	//3
	Memory_Buffer[4] = RT_or_RD;		//4
  Memory_Buffer[5] = pc;

        return Memory_Buffer;
};
vector<int> Memory::Send_FU_Mem_To_Execute(vector <int> IExecute_Buffer)
{
  if(IExecute_Buffer[9] < 0)
  {
      vector<int> temp(4);
      return temp;
  }
        //Extracting Signals from IExecute Buffer
        int RegWrite = IExecute_Buffer[0],
                MemToReg = IExecute_Buffer[1],
                ALU_Result = IExecute_Buffer[6],
                RT_or_RD = IExecute_Buffer[7];

        //Mem_Forwarding_Unit [Size = 4]

	Mem_Forwarding_Unit[0] = RegWrite;		//0
	Mem_Forwarding_Unit[1] = MemToReg;		//1
	Mem_Forwarding_Unit[2] = ALU_Result;		//2
	Mem_Forwarding_Unit[3] = RT_or_RD;	//3

													//Mem_Forwarding_Unit is the full buffer of WB + ALU_Result + RT/RD Address
	return Mem_Forwarding_Unit;
};
Memory::~Memory()
{};
