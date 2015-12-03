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
#include <stack>
using namespace std;

class Decode{
private:
	vector<int> IFB;
	vector<int> *RegFile;
	int branch;
    void opCodeDecoder(int a, int func, std::vector<int> F_DM, std::vector<int> F_WB);

public:
	int pc;
	stack<int> returnStack;
	vector<int> decodeBuffer;
	Decode();
	~Decode();
	void init(vector<int> *rf);
    vector<int> run(vector<int> ifi, std::vector<int> F_DM, std::vector<int> F_WB);
};

#endif /* defined(__CPU__Decode__) */
