/*THIS IS THE PARSER CLASS. THE RUN METHOD TAKE THE FILENAME TO BE PARSED AND RETURN
THE A VECTOR OF INSTRUCTIONS. IN YOUR MAIN METHOD YOU SHOULD COPY THE VECTOR THAT IS
RETURNTED BY THE RUN METHOD TO ANOTHER VECTOR ie( vector<string>yourvector= parser.run(Text.tx);)
*/
#include "Parser.h"
#include <iostream>
#include<vector>
#include<string>
using namespace std;

Parser::Parser()
{

}

Parser::~Parser()
{

}

vector<string>& Parser::run(string filename)
{
	fin.open(filename);
	while (!fin.eof())
	{
		getline(fin, instruction);
		Ins_Mem.push_back(instruction);
	}
	return Ins_Mem;
}

