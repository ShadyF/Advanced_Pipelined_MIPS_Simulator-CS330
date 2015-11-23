//Memory Stage

#ifndef MEMORY_H
#define MEMORY_H
#include <string>
#include <vector>

using namespace std;


class Memory
{
private:
	
	vector <int> Mem_Forwarding_Unit;		//WB + ALU Result + RT/RD Address
	vector <int> Memory_Buffer;			//Producing Memory_Buffer.
	vector <int> IExecute_Buffer;	//Taking Execute_Buffer.

public:
	Memory();
	vector<int> Memory_run(vector <int> *);			//Run
	vector <int> Send_FU_Mem_To_Execute(int RegWrite, int MemToReg, int MuxResult, int RT_or_RD);		//Forwarding Unit
	~Memory();

};

#endif