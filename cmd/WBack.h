#ifndef WBACK_H
#define WBACK_H
#include <vector>
using namespace std;

//Write Back Stage

class WBack
{
private:
	vector <int> Forwarding_Unit;		//WB + Mux Result + RT/RD Address

public:
	WBack();
	void WB_run(vector <int> *);
	~WBack();
	vector Send_FU_Execute();
	vector <int> Memory_Buffer;			//Taking Memory_Buffer.

};







#endif