#include "Execute.h"
#include <string>
#include <vector>

Execute::Execute()
{}

Execute::~Execute()
{}

std::vector<int> Execute::run(std::vector<int> Decode_buffer, std::vector<int> F_DM,
						      std::vector<int> F_WB)
{
	int alu_first_op, alu_second_op, alu_res;
	int F_1, F_2;							 //forward signals {0, 1, 2}
	int reg_dest = Decode_buffer[5], ALU_op = Decode_buffer[6], ALU_src = Decode_buffer[7];
	int R1 = Decode_buffer[8], R2 = Decode_buffer[9];
	int Imm = Decode_buffer[10];
	int RS_addr = Decode_buffer[11], RT_addr = Decode_buffer[12], RD_addr = Decode_buffer[13];
	int RegWrite_mem = F_DM[0], MemtoReg_mem = F_DM[1], ALU_res_mem = F_DM[2], RTorRD_mem = F_DM[3];
	int RegWrite_wb = F_WB[0], MemtoReg_wb = F_DM[2], WB_data = F_WB[2], RTorRD_wb = F_WB[3];

	//Forward Unit
	if (RegWrite_wb)
	{
		if (RS_addr == RTorRD_wb)
			alu_first_op = WB_data;
		if (RT_addr == RTorRD_wb)
			alu_second_op = WB_data;
	}
	if (RegWrite_mem && !MemtoReg_mem)
	{
		if (RS_addr == RTorRD_mem)
			alu_first_op = ALU_res_mem;
		if (RT_addr == RTorRD_mem)
			alu_second_op = ALU_res_mem;
	}
	if(RegWrite_mem && MemtoReg_mem)
		//stall

	if (ALU_src)
		alu_second_op = Imm;
}
