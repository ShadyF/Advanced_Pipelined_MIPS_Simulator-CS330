#include <vector>
#include "WBack.h"
#include "Memory.h"
using namespace std;

WBack::WBack()
{}

void WBack::init(vector<int>* Regs)
{
  RegFile = Regs;
	WB_Forwarding_Unit.resize(4);
};
WBack::~WBack()
{};

//int Mux_Result;	//ay khara (Register File from Amr)

void WBack::WB_run(vector<int> Memory_Buffer)
{
	// Extracting Memory Buffer
	int RegWrite = Memory_Buffer[0],
		MemToReg = Memory_Buffer[1],
		Mem_Data = Memory_Buffer[2],
		ALU_Result = Memory_Buffer[3],
		RT_or_RD = Memory_Buffer[4];

	if (!MemToReg) //if MemToReg = 0 ALU_Result
		Mux_Result = ALU_Result;
	else if (MemToReg)  //if MemToReg = 1 Mem_Data
		Mux_Result = Mem_Data;

	if (RegWrite)
		RegFile->at(RT_or_RD) = Mux_Result;

};

vector<int> WBack::Send_FU_WB_To_Execute(vector<int> Memory_Buffer)
{
	// Extracting Memory Buffer
	int RegWrite = Memory_Buffer[0],
		MemToReg = Memory_Buffer[1],
		RT_or_RD = Memory_Buffer[4];


	//WB_Forwarding_Unit [Size=4]
	WB_Forwarding_Unit[0] = RegWrite;		//0
	WB_Forwarding_Unit[1] = MemToReg;		//1
	WB_Forwarding_Unit[2] = Mux_Result;	//2
	WB_Forwarding_Unit[3] = RT_or_RD;		//3

												//WB_Forwarding_Unit is the full buffer of WB + MuxResult + RT/RD Address
	return WB_Forwarding_Unit;
};

