#pragma once

struct memoryBlockL{
    int address;
    int size;
    memoryBlockL* next;
    memoryBlockL(int address, int size): address(address), size(size), next(NULL) {}
};