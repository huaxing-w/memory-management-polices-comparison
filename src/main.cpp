#include "../header/binaryBuddy.h"
#include "../header/bestFit.h"
#include "../header/firstFit.h"
#include "../header/worstFit.h"
#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;
using FOUR = int[4];
typedef pair<int,int> pii;

int memorySize=262144;
int randomMod=30;

void function1(int operation,unordered_map<int,FOUR>& record){
    binaryBuddy buddy(memorySize);
    queue<shared_ptr<memoryBlock>>temp;
    auto start = high_resolution_clock::now();
    for(int i=0;i<operation;i++){
        int type=rand()%3;
        if(temp.size()==0) type=0;
        if(type<=1){
            int size=rand()%randomMod+1;
            shared_ptr<memoryBlock> block=buddy.allocate(size);
            temp.push(block);
        }
        else{
            shared_ptr<memoryBlock> block=temp.front();
            temp.pop();
            if(block!=nullptr) buddy.freeMemory(block);
            
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    record[operation][0]=duration.count();
}

void function2(int operation,unordered_map<int,FOUR>& record){
    queue<memoryBlockL*>temp1;
    firstFit ff=firstFit(memorySize);
    auto start = high_resolution_clock::now();
    for(int i=0;i<operation;i++){
        int type=rand()%3;
        if(temp1.size()==0) type=0;
        if(type<=1){
            int size=rand()%randomMod+1;
            memoryBlockL* block=ff.allocate(size);
            temp1.push(block);
        }
        else{
            memoryBlockL* block=temp1.front();
            temp1.pop();
            ff.freeMemory(block);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    record[operation][1]=duration.count();
}

void function3(int operation,unordered_map<int,FOUR>& record){
    queue<memoryBlockL*>temp2;
    worstFit wf=worstFit(memorySize);
    auto start = high_resolution_clock::now();
    for(int i=0;i<operation;i++){
        int type=rand()%3;
        if(temp2.size()==0) type=0;
        if(type<=1){
            int size=rand()%randomMod+1;
            memoryBlockL* block=wf.allocate(size);
            temp2.push(block);
        }
        else{
            memoryBlockL* block=temp2.front();
            temp2.pop();
            wf.freeMemory(block);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    record[operation][2]=duration.count();
}

void function4(int operation,unordered_map<int,FOUR>& record){
    queue<memoryBlockL*>temp3;
    bestFit bf=bestFit(memorySize);
    auto start = high_resolution_clock::now();
    for(int i=0;i<operation;i++){
        int type=rand()%3;
        if(temp3.size()==0) type=0;
        if(type<=1){
            int size=rand()%randomMod+1;
            memoryBlockL* block=bf.allocate(size);
            temp3.push(block);
        }
        else{
            memoryBlockL* block=temp3.front();
            temp3.pop();
            bf.freeMemory(block);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    record[operation][3]=duration.count();
}


int main(){
    
    unordered_map<int,FOUR>record;

    vector<thread>t1;
    for(int i=100;i<=10000;i+=100) t1.push_back(thread(function1,i,ref(record)));    
    
    vector<thread>t2;
    for(int i=100;i<=10000;i+=100) t2.push_back(thread(function2,i,ref(record)));    

    vector<thread>t3;
    for(int i=100;i<=10000;i+=100) t3.push_back(thread(function3,i,ref(record)));    
    
    vector<thread>t4;
    for(int i=100;i<=10000;i+=100) t4.push_back(thread(function4,i,ref(record)));    

    for(auto& i:t1) i.join();
    for(auto& i:t2) i.join();
    for(auto& i:t3) i.join();
    for(auto& i:t4) i.join();


    ofstream MyFile("result.txt");


    for(auto& i:record){
        MyFile<<i.first<<endl;
        MyFile<<i.second[0]<<" "<<i.second[1]<<" "<<i.second[2]<<" "<<i.second[3]<<endl;
    }
    MyFile.close();
    
    
    
    return 0;
}