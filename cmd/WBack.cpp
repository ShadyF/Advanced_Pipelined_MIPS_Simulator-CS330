#include <vector>
#include "WBack.h"

using namespace std;


WBack::WBack()
{};

WBack::~WBack()
{};

void WBack::WB_run(vector<int> * Memory_Buffer)
{
	// Extracting Memory Buffer
	int RegWrite = Memory_Buffer->at(0),
		MemToReg = Memory_Buffer->at(1),
		Mem_Data = Memory_Buffer->at(2),
		ALU_Result = Memory_Buffer->at(3),
		RT_or_RD = Memory_Buffer->at(4);


	//To do...


};

vector<int> WBack::Send_FU_WB_To_Execute(int RegWrite,int MemToReg,int MuxResult, int RT_or_RD)
{
	WB_Forwarding_Unit.resize(4);		//Size to 4

	WB_Forwarding_Unit.push_back(RegWrite);
	WB_Forwarding_Unit.push_back(MemToReg);
	WB_Forwarding_Unit.push_back(MuxResult);
	WB_Forwarding_Unit.push_back(RT_or_RD);	

	//WB_Forwarding_Unit is the full buffer of WB + MuxResult + RT/RD Address
	return WB_Forwarding_Unit;
};


