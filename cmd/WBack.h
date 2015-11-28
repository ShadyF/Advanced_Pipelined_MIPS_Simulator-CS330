#ifndef WBACK_H
#define WBACK_H
#include <vector>
using namespace std;

//Write Back Stage

class WBack
{
public:
	WBack();
  void init(vector<int>* RegFile);
	void WB_run(vector <int>);			//Run (Doesn't return a buffer) (Final Stage)
	vector <int> Send_FU_WB_To_Execute(vector <int>);	//returns Forwarding Unit
	~WBack();

  int pc;
	vector <int> WB_Forwarding_Unit;		//WB + Mux Result + RT/RD Address
	//vector <int> Memory_Buffer;			//Taking Memory_Buffer.
	vector<int>* RegFile;
	int Mux_Result;
};

#endif
