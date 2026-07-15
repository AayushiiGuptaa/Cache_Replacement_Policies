#ifndef RANDOM_POLICY_H
#define RANDOM_POLICY_H

#include "ReplacementPolicy.h"
#include <vector>

class RandomPolicy : public ReplacementPolicy {
private:
    std::vector<int> blocks;

public:
    RandomPolicy();

    void access(int index) override;
    void insert(int index) override;
    int chooseVictim() override;
    const char* name() const override;
};

#endif