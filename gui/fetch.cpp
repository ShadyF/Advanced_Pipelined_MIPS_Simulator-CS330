#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#include "Fetch.h"

using namespace std;

Fetch::Fetch()
{
	IF_ID_Buffer.resize(2);
	BTB.resize(10);
	for (int i = 0; i < 10; i++)
	{
		BTB[i].resize(3);
		for (int j = 0; j < 3; j++)
			BTB[i][j] = -1;
	}
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


vector<int> Fetch::run(bool* stall, bool check_branch, int pc_inst, int branch_signal, int jump_flag, int jump_addr)
{
	int instruction;

	if (check_branch && BTB[pc_inst % 10][2] != branch_signal)
	{
		BTB[pc_inst % 10][2] = !BTB[pc_inst % 10][2];
		pc = BTB[pc_inst % 10][1];
		instruction = temp.at(pc);
		IF_ID_Buffer[0] = pc;
		IF_ID_Buffer[1] = instruction;
		pc++;
	}

	else if (jump_flag)
	{
		pc = jump_addr;
		instruction = temp.at(pc);
		IF_ID_Buffer[0] = pc;
		IF_ID_Buffer[1] = instruction;
		pc++;
	}

	else if (pc < temp.size() && pc >= 0)
	{
		instruction = temp.at(pc);
		IF_ID_Buffer[0] = pc;
		IF_ID_Buffer[1] = instruction;
		pc++;
	}
	else
	{
		pc = -1;
		IF_ID_Buffer[0] = pc;
		IF_ID_Buffer[1] = 0;
	}

	int opcode = (IF_ID_Buffer[1] >> 26) & 63;
	int imm = IF_ID_Buffer[1] & 65535;
	if (opcode == 4)
	{
		if (BTB[pc - 1 % 10][0] == -1)
		{
			BTB[pc - 1 % 10][0] = pc - 1;
			BTB[pc - 1 % 10][1] = pc + imm;
			BTB[pc - 1 % 10][2] = 0;
			pc++;
		}
		else
			pc = (BTB[pc - 1 % 10][2]) ? BTB[pc - 1 % 10][1] : pc + 1;
	}
	return IF_ID_Buffer;
}
