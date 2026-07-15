#ifndef ADAPTIVE_POLICY_H
#define ADAPTIVE_POLICY_H

#include "ReplacementPolicy.h"
#include <list>
#include <unordered_map>
#include <vector>
#include <deque>

class AdaptivePolicy : public ReplacementPolicy
{
private:
    enum Mode { MODE_LRU, MODE_RANDOM };
    Mode mode;

    // Recency order, always maintained regardless of mode (front = most recently used)
    std::list<int> lruOrder;
    std::unordered_map<int, std::list<int>::iterator> lruPos;

    // Set of currently occupied line indices, always maintained (for random victim pick)
    std::vector<int> present;
    std::unordered_map<int, int> presentPos; // index -> position within `present`

    // Sliding window of recent hit/miss outcomes, used to decide when to switch modes
    std::deque<bool> history;
    int windowSize;
    int hitsInWindow;

    long long accessCount;
    long long lastReturnToLruAccess; // only gates switching back to LRU
    int returnToLruCooldown;
    bool verbose;

    void recordOutcome(bool hit);
    void removeIndex(int index);

public:
    explicit AdaptivePolicy(int windowSize = 50, bool verbose = false);

    void access(int index) override;
    void insert(int index) override;
    int chooseVictim() override;
    const char* name() const override;

    // Manual override
    void switchPolicy(bool lruEnabled);
};

#endif