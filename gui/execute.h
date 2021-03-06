#ifndef EXECUTE_H
#define	EXECUTE_H

class Execute {

private:
  int alu_first_op, alu_second_op, alu_res, Zero;
  int reg_dest, ALU_op, ALU_src;
  int R1, R2;
  int Imm;
  int RS_addr, RT_addr, RD_addr;
  int RegWrite_mem, MemtoReg_mem, ALU_res_mem, RTorRD_mem;
  int RegWrite_wb, MemtoReg_wb, WB_data, RTorRD_wb;
  std::vector<int> Execute_buffer;
  std::vector<int> FU_DM;
  std::vector<int> FU_WB;


public:
  int pc;
  bool stall = 0;
        Execute();
        ~Execute();
        std::vector<int> run(std::vector<int> Decode_buffer, std::vector<int> F_DM,
                       std::vector<int> F_WB);

};


#endif
