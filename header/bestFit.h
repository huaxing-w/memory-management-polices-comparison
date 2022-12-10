#include "bits/stdc++.h"
#include "memoryBlockL.h"
using namespace std;

class bestFit{
    public:
    bestFit(int s);
    memoryBlockL* allocate(int size);
    void freeMemory(memoryBlockL* block);
    void printMemory();
    
    private:
    memoryBlockL* head;
    void clearUp();
    void mergeMemory();
    void sortMemory();
};