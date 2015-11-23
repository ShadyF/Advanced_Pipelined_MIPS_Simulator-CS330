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



};


