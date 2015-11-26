#include "CPU.h"
#include <iostream>
using namespace std;

int main()
{
	//vector<int>* DataMemory = new vector<int>;
	//DataMemory->resize(2);
	//DataMemory->at(0) = 123921;
	//vector<int>* Regs = new vector<int>;
	//Regs->resize(3);
	//Regs->at(2) = 390;
	//Memory Mem(DataMemory);
	//WBack back2back(Regs);

	//vector<int> DF{1,0,0,0,0,1, 5, 0, 5, 8, 592, 0, 1, 1};
	//vector<int> FMEM{ 0, 0, 5, 1 };
	//vector<int> FWB{ 0, 0, 9, 1 };
	//vector<int> MemBuf;
	//vector<int> ExBuf;
	//Execute X2X;
	//ExBuf = X2X.run(DF, FMEM,FWB);

	//MemBuf = Mem.Memory_run(ExBuf);
	//back2back.WB_run(MemBuf);

	//vector<int> bb;
	//bb = back2back.Send_FU_WB_To_Execute(MemBuf);

	//for (auto x : bb)
	//	cout << x << endl;
	//for (int i = 0; i < 2; i++)
	//	cout << "DataMem " << i <<": " << DataMemory->at(i) <<endl;

	//for (int i = 0; i < 3; i++)
	//	cout << "Regs " << i <<": "<< Regs->at(i) << endl;
	//cout << (5 ^ 8);
  CPU CP("H:/AUC/Current Semester/CS330 Project/Advanced_Pipelined_MIPS_Simulator-CS330/cmd/Text.txt");
  

  for(int i = 0; i<16; i++) {
    CP.run_one_cycle();
  }

  for(int i = 0; i < 16; i++)
    cout << CP.Regs->at(i) <<endl;

  cout<<endl;
for(int i = 0; i < 18; i++)
  cout << CP.DataMemory->at(i) <<endl;
}
