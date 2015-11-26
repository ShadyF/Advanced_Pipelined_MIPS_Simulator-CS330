//Memory Stage
#ifndef MEMORY_H
#define MEMORY_H
#include <string>
#include <vector>
using namespace std;


class Memory
{
public:
	Memory();
  void init(vector<int>*);
	vector<int> Memory_run(vector <int>);			//Run and return Memory Buffer for WB
	vector <int> Send_FU_Mem_To_Execute(vector <int>);		// returns Forwarding Unit,
															// takes execute buffer from CPU
	~Memory();

	vector <int> Mem_Forwarding_Unit;		//WB + ALU Result + RT/RD Address
	vector <int> Memory_Buffer;			//Producing Memory_Buffer.
	vector <int>* DataMemory;
};

#endif
