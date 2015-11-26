#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#include "Fetch.h"

using namespace std;

Fetch::Fetch()
{
  IF_ID_Buffer.resize(2);
}

Fetch::~Fetch()
{

}

void Fetch::init(vector<int> Instruction_Mem)
{
	pc = -1;
	for (int i = 0; i < Instruction_Mem.size(); i++)
	{
		temp.push_back(Instruction_Mem[i]);
	}
}


vector<int> Fetch:: run(int pc_branch, int branch_signal, int jump_flag, int jump_addr)
{
	int instruction;

	if (branch_signal == 1)
		pc += pc_branch;
	else
		pc += 1;

  if(jump_flag)
    pc = jump_addr;

	instruction = temp.at(pc);
  IF_ID_Buffer[0] = pc;
  IF_ID_Buffer[1] = instruction;

	return IF_ID_Buffer;
}