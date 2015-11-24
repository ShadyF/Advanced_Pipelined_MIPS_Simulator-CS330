/*THIS IS THE PARSER CLASS. THE RUN METHOD TAKE THE FILENAME TO BE PARSED AND RETURN
THE A VECTOR OF INSTRUCTIONS. IN YOUR MAIN METHOD YOU SHOULD COPY THE VECTOR THAT IS
RETURNTED BY THE RUN METHOD TO ANOTHER VECTOR ie( vector<string>yourvector= parser.run(Text.tx);)
*/
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include "Parser.h"

using namespace std;

Parser::Parser()
{

}

Parser::~Parser()
{

}

vector<int> Parser::run(string filename)  
{
	fin.open(filename);
  if(!fin.is_open())
  {
    cout << "File not found";
    return Ins_mem_int;
  }
	while (!fin.eof()) 
	{
		getline(fin, instruction);
		Ins_Mem.push_back(instruction);

	}
	for (int i = 0; i < Ins_Mem.size(); i++)
	{
		if (Ins_Mem[i] == "")
		{
			Ins_Mem.resize(i);
		}
	}




	//Getting instruction byt instruction from Ins_Mem, decide which operation then insert the value of instruction(int)
	// in ins_mem_int then return the vector ins_mem_int
	for (int i = 0; i < Ins_Mem.size(); i++)
	{

		string ins_tofetch = "";                      //instruction from ins_mem
		string s = "";                               //register $s
		string temp = "";                           // temporary
		string t = "";                             // register $t
		string d = "";                            // register $d
		string imm = "";                         // imm(16bit)
		string target = "";                     // target(26bit)
		string binary_ins = "";                // instruction in binary
		string Op;      
		int j = 0;
		int start = 0;
		int no_comma = 0;
		bitset<5> regd, regs, regt;
		bitset<16> regimm;
		bitset<26>regtarget;


		ins_tofetch = Ins_Mem[i];

//////////////////INDICATE THE OPERATION TYPE AND THE STARTING POINTER FOR FETCHING THE FRIRST OPEAND IN EACH INSTRUCTION///////////////////////////////
		if ((ins_tofetch[j] == 'a') && (ins_tofetch[j + 1] == 'd') && (ins_tofetch[j + 2] == 'd') && (ins_tofetch[j + 3] == ' '))
		{
			Op = "add";
			start = 4;
		}
		else if ((ins_tofetch[j] == 'a') && (ins_tofetch[j + 1] == 'd') && (ins_tofetch[j + 2] == 'd') && (ins_tofetch[j + 3] == 'i'))
		{
			Op = "addi";
			start = 5;

		}
		else if ((ins_tofetch[j] == 'x') && (ins_tofetch[j + 1] == 'o') && (ins_tofetch[j + 2] == 'r'))
		{
			Op = "xor";
			start = 4;
		}
		else if ((ins_tofetch[j] == 'l') && (ins_tofetch[j + 1] == 'w'))
		{
			Op = "lw";
			start = 3;
		}
		else if ((ins_tofetch[j] == 's') && (ins_tofetch[j + 1] == 'w'))
		{
			Op = "sw";
			start = 3;
		}
		else if ((ins_tofetch[j] == 'b') && (ins_tofetch[j + 1] == 'l') && (ins_tofetch[j + 2] == 'e'))
		{
			Op = "ble";
			start = 4;
		}
		else if ((ins_tofetch[j] == 'j') && (ins_tofetch[j + 1] == ' '))
		{
			Op = "j";
			start = 2;
		}
		else if ((ins_tofetch[j] == 'j') && (ins_tofetch[j + 1] == 'r'))
		{
			Op = "jr";
			start = 3;
		}
		else if ((ins_tofetch[j] == 'j') && (ins_tofetch[j + 1] == 'a') && (ins_tofetch[j + 2] == 'l'))
		{
			Op = "jal";
			start = 4;
		}
		else if ((ins_tofetch[j] == 's') && (ins_tofetch[j + 1] == 'l') && (ins_tofetch[j + 2] == 't'))
		{
			Op = "slt";
			start = 4;
		}
		else if ((ins_tofetch[j] == 'j') && (ins_tofetch[j + 1] == 'u') && (ins_tofetch[j + 2] == 'm') && (ins_tofetch[j + 3] == 'p'))
		{
			Op = "jump";
			start = 5;
		}
		else if ((ins_tofetch[j] == 'r') && (ins_tofetch[j + 1] == 'e') && (ins_tofetch[j + 2] == 't') && (ins_tofetch[j + 3] == 'u') && (ins_tofetch[j + 4] == 'r') && (ins_tofetch[j + 5] == 'n'))
		{
			Op = "return";
			start = 7;
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////CHECK THE TYPE OF OPERATION THEN INSERT ITS INT VALUE IN THE INS_MEM_INT VECTOR/////////////////////////////////////////////////////////////
		if (Op == "add")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $d
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					d += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is $s
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					s += ins_tofetch[i];
				}
				// if you find 2 commas and didnt find a space then this is $t
				else if ((no_comma == 2) && (ins_tofetch[i] != ' '))
				{
					t += ins_tofetch[i];
				}
			}

			// int representation of d,s,t
			regd = stoi(d);
			regs = stoi(s);
			regt = stoi(t);
			binary_ins = "000000" + regs.to_string() + regt.to_string() + regd.to_string() + "00000100000";
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}

		else if (Op == "addi")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $t
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					t += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is $s
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					s += ins_tofetch[i];
				}
				// if you find 2 commas and didnt find a space then this is imm
				else if ((no_comma == 2) && (ins_tofetch[i] != ' '))
				{
					imm += ins_tofetch[i];
				}
			}
		
			// int representation of $t,$s,imm
			regt = stoi(t);
			regs = stoi(s);
			regimm = stoi(imm);


			binary_ins = "001000" + regs.to_string() + regt.to_string() + regimm.to_string();
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}

		else if (Op == "xor")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $d
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					d += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is $s
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					s += ins_tofetch[i];
				}
				// if you find 2 commas and didnt find a space then this is $t
				else if ((no_comma == 2) && (ins_tofetch[i] != ' '))
				{
					t += ins_tofetch[i];
				}
			}
			// int representation of operands
			regd = stoi(d);
			regs = stoi(s);
			regt = stoi(t);
			binary_ins = "000000" + regs.to_string() + regt.to_string() + regd.to_string() + "00000" + "100110";
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}

		else if (Op == "lw")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $t
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					t += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is imm($s)
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					temp += ins_tofetch[i];
				}

			}
			imm = temp.substr(0, temp.find('('));
			s = temp.substr(temp.find('(') + 1, temp.size() - imm.size() - 2);
			regt = stoi(t);
			regimm = stoi(imm);
			regs = stoi(s);

			binary_ins = "100011" + regs.to_string() + regt.to_string() + regimm.to_string();
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}
		else if (Op == "sw")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $t
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					t += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is imm($s)
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					temp += ins_tofetch[i];
				}

			}
			imm = temp.substr(0, temp.find('('));
			s = temp.substr(temp.find('(') + 1, temp.size() - imm.size() - 2);
			regt = stoi(t);
			regimm = stoi(imm);
			regs = stoi(s);
			binary_ins = "101011" + regs.to_string() + regt.to_string() + regimm.to_string();
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}

		else if (Op == "j")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is target address
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					target += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				regtarget = stoi(target);
				binary_ins = "000010" + regtarget.to_string();
				bitset<32> int_ins(binary_ins);
				Ins_mem_int.push_back(int(int_ins.to_ulong()));

			}

		}

		else if (Op == "jal")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is target address
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					target += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				regtarget = stoi(target);
				binary_ins = "000011" + regtarget.to_string();
				bitset<32> int_ins(binary_ins);
				Ins_mem_int.push_back(int(int_ins.to_ulong()));

			}

		}
		else if (Op == "jr")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is target address
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					s += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				regs = stoi(s);
				binary_ins = "000000" + regs.to_string() + "000000000000000001000";
				bitset<32> int_ins(binary_ins);
				Ins_mem_int.push_back(int(int_ins.to_ulong()));

			}

		}
		else if (Op == "ble")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $t
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					t += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is $s
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					s += ins_tofetch[i];
				}
				// if you find 2 commas and didnt find a space then this is imm
				else if ((no_comma == 2) && (ins_tofetch[i] != ' '))
				{
					imm += ins_tofetch[i];
				}
			}
			regt = stoi(t);
			regs = stoi(s);
			regimm = stoi(imm);

			binary_ins = "000100" + regs.to_string() + regt.to_string() + regimm.to_string();
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}

		else if (Op == "slt")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is $d
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					d += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				// if you find a comma and didnt find a space then this is $s
				else if ((no_comma == 1) && (ins_tofetch[i] != ' '))
				{
					s += ins_tofetch[i];
				}
				// if you find 2 commas and didnt find a space then this is t
				else if ((no_comma == 2) && (ins_tofetch[i] != ' '))
				{
					t += ins_tofetch[i];
				}
			}
			regd = stoi(d);
			regs = stoi(s);
			regt = stoi(t);
			binary_ins = "000000" + regs.to_string() + regt.to_string() + regd.to_string()+ "00000101010";
			bitset<32> int_ins(binary_ins);
			Ins_mem_int.push_back(int(int_ins.to_ulong()));

		}

		else if (Op == "jump")
		{
			for (int i = start; i < ins_tofetch.length(); i++)
			{
				// if you find no comma , space, and count=0 then this is target address
				if ((ins_tofetch[i] != ' ') && (ins_tofetch[i] != ',') && (no_comma == 0))
				{
					target += ins_tofetch[i];
				}
				// if you find a comma then ++ number of commas
				else if (ins_tofetch[i] == ',')
				{
					++no_comma;
				}
				regtarget = stoi(target);
				binary_ins = "000001" + regtarget.to_string();
				bitset<32> int_ins(binary_ins);
				Ins_mem_int.push_back(int(int_ins.to_ulong()));

			}

		}

	}
	return Ins_mem_int;

}