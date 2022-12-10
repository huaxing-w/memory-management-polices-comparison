#include "bits/stdc++.h"
using namespace std;

struct memoryBlock {
    int index;
    int size;
    int start;
    int end;
    bool isFree;
    int memoryLeft;
};

class binaryBuddy{
    public:
    vector<shared_ptr<memoryBlock>> tree;
    binaryBuddy(int size);
    shared_ptr<memoryBlock> allocate(int size);
    void freeMemory(shared_ptr<memoryBlock> block);
    
    private:
    
    void populateFree(int index);
    void populateAllocate(int index);
    shared_ptr<memoryBlock> findMemoryBlock(int size,int index);
    void buildTree(int size,int index,int start);
};

