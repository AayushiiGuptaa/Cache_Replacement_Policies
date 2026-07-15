#ifndef FIFO_POLICY_H
#define FIFO_POLICY_H

#include "ReplacementPolicy.h"
#include <queue>

class FIFOPolicy : public ReplacementPolicy {
private:
    std::queue<int> fifoQueue;

public:
    void access(int index) override;
    void insert(int index) override;
    int chooseVictim() override;
    const char* name() const override;
};

#endif