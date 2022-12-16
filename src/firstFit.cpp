#include "../header/firstFit.h"


firstFit::firstFit(int size) {
    head = new memoryBlockL(0, size);
}

void firstFit::clearUp(){
    memoryBlockL* dummy=new memoryBlockL(-1,-1);
    dummy->next=head;
    memoryBlockL* cur=head;
    memoryBlockL* perv=dummy;
    while(cur){
        memoryBlockL* nxt=cur->next;
        if(cur->size==0){
            perv->next=nxt;
            cur=nxt;
        }
        else{
            perv=cur;
            cur=nxt;
        }
    }
    head=dummy->next;
}

memoryBlockL* firstFit::allocate(int size) {
    memoryBlockL* cur=head;
    while(cur){
        if(cur->size>=size){
            memoryBlockL* newBlock = new memoryBlockL(cur->address, size);
            cur->address+=size;
            cur->size-=size;
            clearUp();
            return newBlock;
        }
        cur=cur->next;
    }
    return NULL;
}

void firstFit::freeMemory(memoryBlockL* block) {
    block->next=head;
    head=block;
    sortMemory();
    mergeMemory();

}

void firstFit::printMemory() {
    memoryBlockL* cur=head;
    while(cur){
        cout<<"[address:"<<cur->address<<" size:"<<cur->size<<"]";
        if(cur->next) cout<<"->";
        cur=cur->next;
    }
    cout<<endl;
}

void firstFit::mergeMemory(){
    memoryBlockL* dummy=new memoryBlockL(-1,-1);
    memoryBlockL* perv=dummy;
    memoryBlockL* cur=head;
    perv->next=cur;
    while(cur->next){
        memoryBlockL* next=cur->next;
        if(perv->address==-1){
            perv=cur;
            cur=next;
            continue;
        }
        if(perv->address+perv->size==cur->address){
            perv->size+=cur->size;
            cur=next;
            perv->next=cur;
        }
        else{
            perv=cur;
            cur=next;
        }
    }
    if(perv->address+perv->size==cur->address){
            perv->size+=cur->size;
            perv->next=nullptr;
        }
    head=dummy->next;
}

void firstFit::sortMemory() {
    function<memoryBlockL*(memoryBlockL*,memoryBlockL*)>merge=[&](memoryBlockL* a, memoryBlockL* b){
        if(!a) return b;
        if(!b) return a;
        if(a->address<b->address){
            a->next=merge(a->next,b);
            return a;
        }
        b->next=merge(a,b->next);
        return b;
    };

    function<memoryBlockL*(memoryBlockL*,memoryBlockL*)>sortFunc=[&](memoryBlockL* head,memoryBlockL* tail)->memoryBlockL*{
        if(!head){
            return nullptr;
        }
        if(head->next==tail){
            head->next=nullptr;
            return head;
        }
        memoryBlockL* slow=head;
        memoryBlockL* fast=head;
        while(fast!=tail && fast->next!=tail){
            slow=slow->next;
            fast=fast->next->next;
        }
        memoryBlockL* mid=slow;
        return merge(sortFunc(head,mid),sortFunc(mid,tail));
    };
    head=sortFunc(head,NULL);
}

int firstFit::findSize() {
    int size=0;
    memoryBlockL* cur=head;
    while(cur){
        size+=sizeof(cur);
        cur=cur->next;
    }
    return size;
}