#include <vector>
#include "WBack.h"
#include "Memory.h"
using namespace std;

WBack::WBack()
{};
WBack::~WBack()
{};

int Mux_Result;	//ay khara (Register File from Amr)

void WBack::WB_run(vector<int> Memory_Buffer)
{
	// Extracting Memory Buffer
	int RegWrite = Memory_Buffer[0],
		MemToReg = Memory_Buffer[1],
		Mem_Data = Memory_Buffer[2],
		ALU_Result = Memory_Buffer[3],
		RT_or_RD = Memory_Buffer[4];

	if (RegWrite && !MemToReg)
		Mux_Result = ALU_Result;
	else if (RegWrite && MemToReg)
		Mux_Result = Mem_Data;

};

vector<int> WBack::Send_FU_WB_To_Execute(vector<int> Memory_Buffer) 
{
	// Extracting Memory Buffer
	int RegWrite = Memory_Buffer[0],
		MemToReg = Memory_Buffer[1],
		RT_or_RD = Memory_Buffer[4];


	//WB_Forwarding_Unit [Size=4]
	WB_Forwarding_Unit.push_back(RegWrite);		//0
	WB_Forwarding_Unit.push_back(MemToReg);		//1
	WB_Forwarding_Unit.push_back(Mux_Result);	//2
	WB_Forwarding_Unit.push_back(RT_or_RD);		//3

	//WB_Forwarding_Unit is the full buffer of WB + MuxResult + RT/RD Address
	return WB_Forwarding_Unit;
};


