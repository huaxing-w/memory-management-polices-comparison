#include "bits/stdc++.h"
#include "memoryBlockL.h"
using namespace std;

class worstFit{
    public:
    worstFit(int s);
    memoryBlockL* allocate(int size);
    void printMemory();
    void freeMemory(memoryBlockL* block);

    private:
    memoryBlockL* head;
    void mergeMemory();
    void sortMemory();
    void clearUp();
};