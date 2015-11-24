#ifndef CPU_H
#define CPU_H

class CPU
{
private:
	vector<int> Fetch_buffer, Decode_buffer, Execute_buffer, Memory_buffer, WB_buffer;
	
public:
	vector<int> Regs;
	vector<int> Ins_memory;
	int clock;
	
	CPU(); 				//should take text file here
	~CPU();
	void run_one_cycle();
	void rst();

};
#endif
