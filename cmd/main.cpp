#include <iostream>
#include <vector>
#include "CPU.h"
using namespace std;

int main()
{
  CPU CP("Text");
  for(auto x : CP.InsMemory)
    cout << x <<endl;
}