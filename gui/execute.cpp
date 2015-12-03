#include <string>
#include <vector>
#include <iostream>
#include "Execute.h"

Execute::Execute()
{
        Execute_buffer.resize(10);
        FU_DM.resize(4);
        FU_WB.resize(4);
}

Execute::~Execute()
{}

std::vector<int> Execute::run(std::vector<int> Decode_buffer, std::vector<int> F_DM,
        std::vector<int> F_WB)
{
        pc = Decode_buffer[16];
        if(pc < 0)
        {
            std::vector<int> temp(10);
            temp[9] = -1;
            return temp;
        }
        reg_dest = Decode_buffer[5]; ALU_op = Decode_buffer[6]; ALU_src = Decode_buffer[7];
        R1 = Decode_buffer[8]; R2 = Decode_buffer[9];
        Imm = Decode_buffer[10];
        RS_addr = Decode_buffer[11]; RT_addr = Decode_buffer[12]; RD_addr = Decode_buffer[13];
        RegWrite_mem = F_DM[0]; MemtoReg_mem = F_DM[1]; ALU_res_mem = F_DM[2]; RTorRD_mem = F_DM[3];
        RegWrite_wb = F_WB[0]; MemtoReg_wb = F_DM[2]; WB_data = F_WB[2]; RTorRD_wb = F_WB[3];

        if(stall)
          {
            RegWrite_mem = F_WB[0]; MemtoReg_mem = F_WB[1]; ALU_res_mem = F_WB[2]; RTorRD_mem = F_WB[3];
            RegWrite_wb = FU_WB[0]; MemtoReg_wb = FU_DM[2]; WB_data = FU_WB[2]; RTorRD_wb = FU_WB[3];
          }

	//Forward Unit
	alu_first_op = R1; alu_second_op = R2;
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
		R2 = ALU_res_mem;
	}
	if (RegWrite_mem && MemtoReg_mem && !stall)
		stall = 1;
	else if(RegWrite_mem && MemtoReg_mem && stall)
	  {
	    stall = 0;
	    if (RS_addr == RTorRD_mem)
		    alu_first_op = ALU_res_mem;
	    if (RT_addr == RTorRD_mem)
		    alu_second_op = ALU_res_mem;
	    R2 = ALU_res_mem;
	  }
	else
	  stall = 0;
	if (ALU_src)
		alu_second_op = Imm;
	//ALU Operation
	switch (ALU_op)
	{
	case 0:
		alu_res = alu_first_op + alu_second_op;
		break;
		//case 1://ble
    case 2://slt
        alu_res = (alu_first_op < alu_second_op) ? 1 : 0;
        break;
	case 3://add
		alu_res = alu_first_op + alu_second_op;
		break;
	case 4://addi
		alu_res = alu_first_op + alu_second_op;
		break;
	case 5://xor
		alu_res = alu_first_op ^ alu_second_op;
		break;
		//case 6: //j jal jr
	default:
		alu_res = -1;
	}

	Zero = (alu_res == 0) ? 1 : 0;

	for (int i = 0; i<5; i++)
		Execute_buffer[i] = Decode_buffer[i];
	Execute_buffer[5] = Zero;
	Execute_buffer[6] = alu_res;
	Execute_buffer[7] = (reg_dest) ? RD_addr : RT_addr;
	Execute_buffer[8] = R2;
  Execute_buffer[9] = pc;
  FU_DM = F_DM;
  FU_WB = F_WB;
        return Execute_buffer;

}
