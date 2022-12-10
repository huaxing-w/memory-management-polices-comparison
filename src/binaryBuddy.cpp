#include "../header/binaryBuddy.h"


binaryBuddy::binaryBuddy(int size){
    tree.resize(2*size-1);
    buildTree(size,0,0);
}

shared_ptr<memoryBlock> binaryBuddy::allocate(int size){
    int inputSize=1;
    while(inputSize<max(size,4)){
        inputSize=inputSize<<1;
    }
    int index=0;
    shared_ptr<memoryBlock> block=findMemoryBlock(inputSize,index);
    if(block==nullptr){
        return nullptr;
    }
    populateAllocate(block->index);
    return block;
}

void binaryBuddy::freeMemory(shared_ptr<memoryBlock> block){
    block->isFree=true;
    populateFree(block->index);
}

void binaryBuddy::populateFree(int index){
    tree[index]->isFree=true;
    tree[index]->memoryLeft=tree[index]->size;
    if(index==0){
        return;
    }
    
    if(index%2==0){
        if(tree[index-1]->isFree){
            int parentIndex=(index-1)/2;
            tree[parentIndex]->isFree=true;
            populateFree(parentIndex);
        }
    }
    else{
        if(tree[index+1]->isFree){
            int parentIndex=(index)/2;
            tree[parentIndex]->isFree=true;
            populateFree(parentIndex);
        }
    } 
}


void binaryBuddy::populateAllocate(int index){
    if(index==0){
        return;
    }

    if(index%2==0){
        if(!tree[index-1]->isFree){
            int parentIndex=(index-1)/2;
            tree[parentIndex]->isFree=false;
            populateAllocate(parentIndex);
        }
    }
    else{
        if(!tree[index+1]->isFree){
            int parentIndex=(index)/2;
            tree[parentIndex]->isFree=false;
            populateAllocate(parentIndex);
        }
    }
}

shared_ptr<memoryBlock> binaryBuddy::findMemoryBlock(int size,int index){
    if(tree[index]->size<size){
        return nullptr;
    }
    tree[index]->memoryLeft-=size;
    if(tree[index]->size == size){
        tree[index]->isFree=false;
        return tree[index];
    }
    if(tree[index]->size>size){
        if(tree[2*index+1]->isFree && tree[2*index+1]->memoryLeft>=size){
            return findMemoryBlock(size,2*index+1);
        }
        else if(tree[2*index+2]->isFree && tree[2*index+2]->memoryLeft>=size){
            return findMemoryBlock(size,2*index+2);
        }
        else{
            return nullptr;
        }
    }
}

void binaryBuddy::buildTree(int size,int index,int start){
    auto memory=make_shared<memoryBlock>();
    memory->index=index;
    memory->size=size;
    memory->start=start;
    memory->end=start+size-1;
    memory->isFree=true;
    memory->memoryLeft=size;
    tree[index]=memory;

    if(size==4){
        return;
    }
    buildTree(size/2,2*index+1,start);
    buildTree(size/2,2*index+2,start+size/2);
}
