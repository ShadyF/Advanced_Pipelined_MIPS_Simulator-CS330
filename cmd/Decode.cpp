//
//  Decode.cpp
//  CPU
//
//  Created by Amr on 11/23/15.
//  Copyright (c) 2015 Amr. All rights reserved.
//

#include "Decode.h"

Decode:: Decode(vector<int> *rf){
    RegFile = *rf;
    decodeBuffer.resize(14);
}

vector<int> Decode:: run(vector<int> *ifi){
    int inst = ifi->at(1);
    
    decodeBuffer.at(13) = (inst >> 11) & 31; //rd
    decodeBuffer.at(12) = (inst >> 16) &  31; //rt
    decodeBuffer.at(11) = (inst >> 21) & 31;//rs
    decodeBuffer.at(10) = inst & 65535; //imm
    int opcode = (inst >> 26) & 63;
    int shamt = (inst >> 6) & 31;
    int func = inst & 63;
    
    opCodeDecoder(opcode, func);
    return decodeBuffer;
}

Decode:: ~Decode(){}

void Decode:: opCodeDecoder(int a, int func){
    
    if(a != 0){
        switch (a) {
            case 8: //addi
                decodeBuffer.at(6) = 4; //aluop
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(7) = 1; //alu src
                decodeBuffer.at(0) = 1; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
                break;
            case 35: //lw
                decodeBuffer.at(6) = 0;
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(7) = 1; //alu src
                decodeBuffer.at(0) = 1; // reg write
                decodeBuffer.at(1) = 1; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 1; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
                break;
            case 43: // sw
                decodeBuffer.at(6) = 0;
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(7) = 1; //alu src
                decodeBuffer.at(0) = 0; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 1; // mem write
                decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
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
                break;
            case 3: // jal didnt do the linkinh part yet
                decodeBuffer.at(6) = 7;
                decodeBuffer.at(7) = 0; //alu src
                decodeBuffer.at(0) = 0; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
                break;
            case 6: //ble
                decodeBuffer.at(6) = 1;
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(9) = RegFile.at(decodeBuffer.at(12)); //r2 = rt
                
                if(decodeBuffer.at(8)<= decodeBuffer.at(9))
                    decodeBuffer.at(2) = 1; // branch
                else
                    decodeBuffer.at(2) = 0; // branch
                
                decodeBuffer.at(7) = 0; //alu src
                decodeBuffer.at(0) = 0; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                
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
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(9) = RegFile.at(decodeBuffer.at(12)); //r2 = rt
                
                decodeBuffer.at(7) = 0; //alu src
                decodeBuffer.at(0) = 1; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 1; // reg dest (1 = rd) , (0 = rt)
                break;
            case 32: // add
                decodeBuffer.at(6) = 3;
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(9) = RegFile.at(decodeBuffer.at(12)); //r2 = rt
                
                decodeBuffer.at(7) = 0; //alu src
                decodeBuffer.at(0) = 1; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 1; // reg dest (1 = rd) , (0 = rt)
                break;
            case 8: //jr
                decodeBuffer.at(6) = 8;
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(9) = RegFile.at(decodeBuffer.at(12)); //r2 = rt
                
                decodeBuffer.at(7) = 0; //alu src
                decodeBuffer.at(0) = 0; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 0; // reg dest (1 = rd) , (0 = rt)
                break;
            case 38: //xor
                decodeBuffer.at(6) = 5;
                decodeBuffer.at(8) = RegFile.at(decodeBuffer.at(11)); //r1 = rs
                decodeBuffer.at(9) = RegFile.at(decodeBuffer.at(12)); //r2 = rt
                
                decodeBuffer.at(7) = 0; //alu src
                decodeBuffer.at(0) = 1; // reg write
                decodeBuffer.at(1) = 0; // memtoreg
                decodeBuffer.at(2) = 0; // branch
                decodeBuffer.at(3) = 0; // mem read
                decodeBuffer.at(4) = 0; // mem write
                decodeBuffer.at(5) = 1; // reg dest (1 = rd) , (0 = rt)
                break;
            default:
                break;
        }
    }
    
}
