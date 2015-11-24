#ifndef WBACK_H
#define WBACK_H
#include <vector>
#include "Memory.h"
using namespace std;

//Write Back Stage

class WBack: public Memory
{
public:
	WBack();
	void WB_run(vector <int>);			//Run (Doesn't return a buffer) (Final Stage)
	vector <int> Send_FU_WB_To_Execute(vector <int>);	//returns Forwarding Unit
	~WBack();

	vector <int> WB_Forwarding_Unit;		//WB + Mux Result + RT/RD Address
	vector <int> Memory_Buffer;			//Taking Memory_Buffer.
};

#endif