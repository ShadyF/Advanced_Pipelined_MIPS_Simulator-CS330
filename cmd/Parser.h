/*THIS IS THE PARSER CLASS. THE RUN METHOD TAKE THE FILENAME TO BE PARSED AND RETURN
THE A VECTOR OF INSTRUCTIONS. IN YOUR MAIN METHOD YOU SHOULD COPY THE VECTOR THAT IS 
RETURNTED BY THE RUN METHOD TO ANOTHER VECTOR ie( vector<string>yourvector= parser.run(Text.tx);) 
*/
#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser
{
private:
	string instruction;                     //instruction parsed
	std::ifstream fin;                          // file stream
	vector<string> Ins_Mem;               // instruction memory(string)
	vector<int>Ins_mem_int;               // instruction memory(int)



public:
	Parser();
	~Parser();
	vector<int> run(string);     // run method that parse the file and fill the instruction memory

};

#endif;