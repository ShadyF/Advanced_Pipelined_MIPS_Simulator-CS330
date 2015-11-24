#include "Fetch.h"
#include<iostream>
#include<vector>
#include<string>
#include<bitset>
using namespace std;

Fetch::Fetch(vector<int> Instruction_Mem)
{
	pc = -1;
	for (int i = 0; i < Instruction_Mem.size(); i++)
	{
		temp.push_back( Instruction_Mem[i]);
	}
}

Fetch::~Fetch()
{

}

vector<int>& Fetch:: run(int pc_branch, int branch_signal)
{
	int instruction;
	if (branch_signal == 1)
	{
		pc += pc_branch;
	}
	else
	{
		pc += 1;
	}
	instruction = temp.at(pc);
	IF_ID_Buffer.push_back(pc);
	IF_ID_Buffer.push_back(instruction);
	return IF_ID_Buffer;
}