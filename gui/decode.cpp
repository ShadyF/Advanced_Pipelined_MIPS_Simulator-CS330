//
//  Decode.cpp
//  CPU
//
//  Created by Amr on 11/23/15.
//  Copyright (c) 2015 Amr. All rights reserved.
//

#include "Decode.h"

Decode::Decode()
{}

void Decode::init(vector<int> *rf){
	RegFile = rf;
	decodeBuffer.resize(18); //adding two more slots, one for jump flag and the other for the address
}

vector<int> Decode::run(vector<int> ifi){
	pc = ifi.at(0);
	if (pc < 0)
	{
		vector<int> temp(17);
		temp[16] = -1;
		return temp;
	}
	int inst = ifi.at(1);
	decodeBuffer.at(13) = (inst >> 11) & 31; //rd
    decodeBuffer.at(12) = (inst >> 16) & 31; //rt
	decodeBuffer.at(11) = (inst >> 21) & 31;//rs
	decodeBuffer.at(15) = inst & 67108863; // jump
	decodeBuffer.at(16) = pc;
	decodeBuffer[17] = 0;

	int imm = inst & 65535;
	if (imm & 0x8000)
		imm = 0xFFFF0000 | imm;
	int opcode = (inst >> 26) & 63;
	int shamt = (inst >> 6) & 31;
	int func = inst & 63;

	decodeBuffer.at(10) = imm; //signed imm
	opCodeDecoder(opcode, func);
	return decodeBuffer;
}

Decode:: ~Decode(){}

void Decode::opCodeDecoder(int a, int func){

	if (a != 0){
		switch (a) {
		case 8: //addi
			decodeBuffer.at(6) = 4; //aluop
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(7) = 1; //alu src
			decodeBuffer.at(0) = 1; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			break;
		case 35: //lw
			decodeBuffer.at(6) = 0;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt
			decodeBuffer.at(7) = 1; //alu src
			decodeBuffer.at(0) = 1; // reg write
			decodeBuffer.at(1) = 1; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 1; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			break;
		case 43: // sw
			decodeBuffer.at(6) = 0;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt

			decodeBuffer.at(7) = 1; //alu src
			decodeBuffer.at(0) = 0; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 1; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			/*for(int i = 0; i<16; i++)
			cout << RegFile->at(i) << " ";*/
			break;
		case 2: // j
			decodeBuffer.at(6) = 6;
			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 0; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 1; //jump flag
			break;
		case 3: // jal didnt do the linkinh part yet
			decodeBuffer.at(6) = 4;
			decodeBuffer.at(8) = decodeBuffer.at(16); //r1 = rs
			//returnStack.push(decodeBuffer.at(8));
			decodeBuffer.at(7) = 1; //alu src
			decodeBuffer.at(0) = 1; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(12) = 15; //rt
			decodeBuffer.at(11) = decodeBuffer.at(16);//rs
            //cout<<decodeBuffer.at(11)<< " "<< decodeBuffer.at(10)<< " "<<decodeBuffer.at;
			decodeBuffer.at(10) = 1; //imm
			decodeBuffer.at(14) = 2; //jump flag
			break;
		case 4: //ble
			decodeBuffer.at(6) = 1;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt
            cout<<decodeBuffer.at(8)<<" "<<decodeBuffer.at(9)<<endl;

			if (decodeBuffer.at(8) <= decodeBuffer.at(9))
				decodeBuffer.at(2) = 1; // branch
			else
				decodeBuffer.at(2) = 0; // branch

			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 0; // reg write
			decodeBuffer.at(1) = 0; // memtoreg

			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			decodeBuffer[17] = 1; //check_branch
			break;
		case 1: // jump procedure should save rs in stack
			decodeBuffer.at(6) = 6; //new opcode for Jump Procedure
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			returnStack.push(decodeBuffer.at(16) + 1);
			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 0; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 1; //jump flag
			break;
		case 63: //return procedure
			decodeBuffer.at(6) = 6; //new opcode for Jump Procedure
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			if (!returnStack.empty()){
				decodeBuffer.at(15) = returnStack.top();
				returnStack.pop();
				decodeBuffer.at(14) = 1; //jump flag
			}
			else{
				decodeBuffer.at(14) = 0;
			}
			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 0; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)

			break;
		default:
			break;
		}
	}
	else{
		switch (func) {
		case 42: // slt
			decodeBuffer.at(6) = 2;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt

			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 1; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 1; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			break;
		case 32: // add
			decodeBuffer.at(6) = 3;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt

			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 1; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 1; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			break;
		case 8: //jr
			decodeBuffer.at(6) = 8;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt

			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 0; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 1; //jump flag
            decodeBuffer.at(15) = RegFile->at(decodeBuffer.at(11));
            //cout<<RegFile->at(decodeBuffer.at(11))<<endl;
            //cout<<decodeBuffer.at(11)<<endl;
			break;
		case 38: //xor
			decodeBuffer.at(6) = 5;
			decodeBuffer.at(8) = RegFile->at(decodeBuffer.at(11)); //r1 = rs
			decodeBuffer.at(9) = RegFile->at(decodeBuffer.at(12)); //r2 = rt

			decodeBuffer.at(7) = 0; //alu src
			decodeBuffer.at(0) = 1; // reg write
			decodeBuffer.at(1) = 0; // memtoreg
			decodeBuffer.at(2) = 0; // branch
			decodeBuffer.at(3) = 0; // mem read
			decodeBuffer.at(4) = 0; // mem write
			decodeBuffer.at(5) = 1; // reg dest (1 = rd) , (0 = rt)
			decodeBuffer.at(14) = 0; //jump flag
			break;
		default:
			break;
		}
	}

}
