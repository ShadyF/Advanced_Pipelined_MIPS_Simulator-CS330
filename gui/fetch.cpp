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
	pc = 0;
	for (int i = 0; i < Instruction_Mem.size(); i++)
	{
		temp.push_back(Instruction_Mem[i]);
	}
}


vector<int> Fetch:: run(int pc_inst, int pc_branch, int branch_signal, int jump_flag, int jump_addr)
{
  int instruction;

  if(branch_signal)
  {
    pc = pc_inst + pc_branch +1;
    instruction = temp.at(pc);
    IF_ID_Buffer[0] = pc;
    IF_ID_Buffer[1] = instruction;
    pc++;
    return IF_ID_Buffer;
  }
  if(jump_flag)
  {
    pc = jump_addr;
    instruction = temp.at(pc);
    IF_ID_Buffer[0] = pc;
    IF_ID_Buffer[1] = instruction;
    pc++;
    return IF_ID_Buffer;
  }

  if(pc < temp.size() && pc >= 0)
  {
    instruction = temp.at(pc);
    IF_ID_Buffer[0] = pc;
    IF_ID_Buffer[1] = instruction;
    pc++;
    return IF_ID_Buffer;
  }
  else
  {
    pc = -1;
    IF_ID_Buffer[0] = pc;
    IF_ID_Buffer[1] = 0;
    return IF_ID_Buffer;
  }
}
