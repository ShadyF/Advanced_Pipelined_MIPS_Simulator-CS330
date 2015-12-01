/*THIS IS THE FETCH STAGE. TO INITILIZE FETCH, PASS THE VECTOR OF INTEGER THAT IS THE OUTPUT OF THE PARSER TO IT. AT INITILIZATION
TH/*THIS IS THE FETCH STAGE. TO INITILIZE FETCH, PASS THE VECTOR OF INTEGER THAT IS THE OUTPUT OF THE PARSER TO IT. AT INITILIZATION
THE PC IS EQUAL TO -1. AFTER THAT PASS TO RUN THE PC_BRANCH AND PC_SIGNAL, IT THEN ADDS ON THE PC+1 OR+PC_BRANCH. AFTER ADDING THE PC IT RETURN
A VECTOR THAT HAS [PC , INSTRUCTION(INT) ].
*/

#ifndef FETCH_H
#define FETCH_H

#include <vector>
using namespace std;

class Fetch
{
private:
	int instruction;                     // instruction
	vector<int> IF_ID_Buffer;           // vector containing pc and instruction that will be passed to the next stage
	vector<int> temp;
	vector<vector <int> > BTB;         // btb table
	int counter = -1;
	int statebit;



public:
	int pc;                               //Program Counter
	int predicted_pc;                    //predicted pc

	Fetch();
	~Fetch();
	void init(vector<int>);            // initilizing by passing vector of instructions (int)
	vector<int> run(bool* stall, bool check_branch, int pc_inst, int branch_signal, int jump_signal, int jump_addr);      // passes to it pc of branch and branch signal. returns pc and instruction

};

#endif
