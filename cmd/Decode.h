//
//  Decode.h
//  CPU
//
//  Created by Amr on 11/23/15.
//  Copyright (c) 2015 Amr. All rights reserved.
//

#ifndef __CPU__Decode__
#define __CPU__Decode__

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

class Decode{
private:
    vector<int> IFB;
    vector<int> RegFile;
    int branch;
    void opCodeDecoder(int a, int func);
    
public:
    vector<int> decodeBuffer;
    Decode(vector<int> *rf);
    ~Decode();
    vector<int> run(vector<int> *ifi);
};

#endif /* defined(__CPU__Decode__) */
