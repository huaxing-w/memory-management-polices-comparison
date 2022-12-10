#include "bits/stdc++.h"
#include "memoryBlockL.h"
using namespace std;

class firstFit{
    public:
    firstFit(int size);
    memoryBlockL* allocate(int size);
    void freeMemory(memoryBlockL* block);
    void printMemory();
    
    private:
    memoryBlockL* head;
    void clearUp();
    void mergeMemory();
    void sortMemory();

};