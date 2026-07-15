#include "FIFOPolicy.h"

void FIFOPolicy::access(int index)
{
    // FIFO does not change order on access
}

void FIFOPolicy::insert(int index)
{
    fifoQueue.push(index);
}

int FIFOPolicy::chooseVictim()
{
    if (fifoQueue.empty())
        return -1;

    int victim = fifoQueue.front();
    fifoQueue.pop();

    return victim;
}

const char* FIFOPolicy::name() const
{
    return "FIFO";
}