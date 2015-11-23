#ifndef WBACK_H
#define WBACK_H
#include <vector>
using namespace std;

//Write Back Stage

class WBack
{
private:
	vector <int> WB_Forwarding_Unit;		//WB + Mux Result + RT/RD Address
	vector <int> Memory_Buffer;			//Taking Memory_Buffer.

public:
	WBack();
	void WB_run(vector <int> *);			//Run
	vector <int> Send_FU_WB_To_Execute(int RegWrite,int MemToReg,int MuxResult,int RT_or_RD);	//Forwarding Unit
	~WBack();


};







#endif