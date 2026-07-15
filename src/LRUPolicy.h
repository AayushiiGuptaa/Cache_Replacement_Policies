#ifndef LRU_POLICY_H
#define LRU_POLICY_H

#include "ReplacementPolicy.h"
#include <list>
#include <unordered_map>

class LRUPolicy : public ReplacementPolicy {
private:
    std::list<int> order;
    std::unordered_map<int, std::list<int>::iterator> position;

public:
    void access(int index) override;
    void insert(int index) override;
    int chooseVictim() override;
    const char* name() const override;
};

#endif