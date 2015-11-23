//Memory Stage

#ifndef MEMORY_H
#define MEMORY_H
#include <string>
#include <vector>

using namespace std;


class Memory
{
private:
	
	vector <int> Memory_Buffer;			//Memory Buffer
	vector <int> Forwarding_Unit;		//WB + ALU Result + RT/RD Address

public:
	Memory();
	void Memory_run(vector <int> *);
	~Memory();

	vector<int> Send_FU_Execute();
	vector <int> IExecute_Buffer;	//Taking Execute_Buffer.

};

#endif