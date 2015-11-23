//
//  Decode.cpp
//  CPU
//
//  Created by Amr on 11/23/15.
//  Copyright (c) 2015 Amr. All rights reserved.
//

#include "Decode.h"

Decode:: Decode(vector<int> * rf){
    RegFile = *rf;
    decodeBuffer.resize(14);
}

void Decode:: run(vector<int> *ifi){
    int inst = ifi->at(1);
    
    int rd  = (inst >> 11) & 31;
    int rt = (inst >> 16) &  31;
    int rs = (inst >> 21) & 31;
    int imm = inst & 65535;
    int opcode = (inst >> 26) & 63;
    int shamt = (inst >> 6) & 31;
    int func = inst & 63;
    
    opCodeDecoder(opcode, func);
    
}

Decode:: ~Decode(){}

void Decode:: opCodeDecoder(int a, int func){
    
    if(a != 0){
        switch (a) {
            case 8:
                decodeBuffer.at(6) = 4;
                break;
            case 35:
                decodeBuffer.at(6) = 0;
                break;
            case 43:
                decodeBuffer.at(6) = 0;
                break;
            case 2:
                decodeBuffer.at(6) = 6;
                break;
            case 3:
                decodeBuffer.at(6) = 7;
                break;
            default:
                break;
        }
    }
    else{
        switch (func) {
            case 42:
                decodeBuffer.at(6) = 2;
                break;
            case 32:
                decodeBuffer.at(6) = 3;
                break;
            case 8:
                decodeBuffer.at(6) = 8;
                break;
            default:
                break;
        }
    }
    
}
