#include <vector>
#include <exception>
#include "Memory.h"

using namespace std;


Memory::Memory()
{};

vector<int> Memory::Memory_run(vector <int> * IExecute_Buffer)
{
	// Extracting IExecute Buffer.
	int RegWrite = IExecute_Buffer->at(0),
		MemToReg = IExecute_Buffer->at(1),
		//^WB
		Branch = IExecute_Buffer->at(2),
		MemRead = IExecute_Buffer->at(3),
		MemWrite = IExecute_Buffer->at(4),
		Zero = IExecute_Buffer->at(5),
		ALU_Result = IExecute_Buffer->at(6),
		RT_or_RD = IExecute_Buffer->at(7);
	int Mem_Data;


	vector<int> DataMemory;		//Data Memory Vector
	DataMemory.resize(32);

	//Nothing for Zero yet.

	if (MemRead && !MemWrite)		//Memory Read is ON
	{
		if (ALU_Result < 0 || ALU_Result > 32)
			Mem_Data = -1;			//out of range
		else
			Mem_Data = DataMemory[ALU_Result];
	}

	//else if (!MemRead && !MemWrite)
		//Mem_Data = ALU_Result;

	if (MemWrite && !MemRead)		//Memory Write is ON
	{
		if (ALU_Result < 0 || ALU_Result > 32)
			throw invalid_argument("Out of range 32 (ALU RESULT) FOR MEMORY WRITE");
		else
			DataMemory.push_back(ALU_Result);
	}


	Memory_Buffer.resize(5);		//Size of buffer for WB Stage
	//Creating Memory_Buffer
	Memory_Buffer.push_back(RegWrite);		//Done
	Memory_Buffer.push_back(MemToReg);		//Done
	//^ WB
	Memory_Buffer.push_back(Mem_Data);		//Done	
	Memory_Buffer.push_back(ALU_Result);	//Done
	Memory_Buffer.push_back(RT_or_RD);		//Done

	return Memory_Buffer;
};

vector<int> Memory::Send_FU_Mem_To_Execute(int RegWrite, int MemToReg, int ALU_Result, int RT_or_RD)
{
	Mem_Forwarding_Unit.resize(4);		//Size to 4

	Mem_Forwarding_Unit.push_back(RegWrite);
	Mem_Forwarding_Unit.push_back(MemToReg);
	Mem_Forwarding_Unit.push_back(ALU_Result);
	Mem_Forwarding_Unit.push_back(RT_or_RD);

	//Mem_Forwarding_Unit is the full buffer of WB + ALU_Result + RT/RD Address
	return Mem_Forwarding_Unit;
};

Memory::~Memory()
{};
