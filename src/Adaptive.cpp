#include "Adaptive.h"
#include <cstdlib>
#include <iostream>

AdaptivePolicy::AdaptivePolicy(int windowSize, bool verbose)
    : mode(MODE_LRU), windowSize(windowSize), hitsInWindow(0),
      accessCount(0), lastReturnToLruAccess(-1000000), returnToLruCooldown(windowSize * 10),
      verbose(verbose)
{
}


void AdaptivePolicy::removeIndex(int index)
{
    auto lit = lruPos.find(index);
    if (lit != lruPos.end())
    {
        lruOrder.erase(lit->second);
        lruPos.erase(lit);
    }

    auto pit = presentPos.find(index);
    if (pit != presentPos.end())
    {
        int pos = pit->second;
        int lastIndex = present.back();

        present[pos] = lastIndex;
        presentPos[lastIndex] = pos;

        present.pop_back();
        presentPos.erase(pit);
    }
}

void AdaptivePolicy::recordOutcome(bool hit)
{
    accessCount++;
    history.push_back(hit);
    if (hit) hitsInWindow++;

    if ((int)history.size() > windowSize)
    {
        if (history.front()) hitsInWindow--;
        history.pop_front();
    }

    if ((int)history.size() == windowSize)
    {
        double hitRate = (double)hitsInWindow / windowSize;

        
        if (mode == MODE_LRU && hitRate < 0.05)
        {
            mode = MODE_RANDOM;
            lastReturnToLruAccess = accessCount; // start the cooldown clock fresh
            if (verbose)
                std::cerr << "[Adaptive] switch -> RANDOM at access " << accessCount
                          << " (window hit rate " << hitRate << ")" << std::endl;
        }
        
        else if (mode == MODE_RANDOM && hitRate > 0.60 &&
                 (accessCount - lastReturnToLruAccess) >= returnToLruCooldown)
        {
            mode = MODE_LRU;
            lastReturnToLruAccess = accessCount;
            if (verbose)
                std::cerr << "[Adaptive] switch -> LRU at access " << accessCount
                          << " (window hit rate " << hitRate << ")" << std::endl;
        }
    }
}

void AdaptivePolicy::access(int index)
{
    auto it = lruPos.find(index);
    if (it != lruPos.end())
    {
        lruOrder.erase(it->second);
        lruOrder.push_front(index);
        lruPos[index] = lruOrder.begin();
    }

    recordOutcome(true);
}

void AdaptivePolicy::insert(int index)
{
    removeIndex(index);

    lruOrder.push_front(index);
    lruPos[index] = lruOrder.begin();

    present.push_back(index);
    presentPos[index] = (int)present.size() - 1;

    recordOutcome(false);
}

int AdaptivePolicy::chooseVictim()
{
    int victim;

    if (mode == MODE_LRU)
    {
        if (lruOrder.empty()) return -1;
        victim = lruOrder.back();
    }
    else
    {
        if (present.empty()) return -1;
        int pos = std::rand() % (int)present.size();
        victim = present[pos];
    }

    removeIndex(victim);
    return victim;
}

const char* AdaptivePolicy::name() const
{
    return (mode == MODE_LRU) ? "Adaptive(LRU)" : "Adaptive(Random)";
}

void AdaptivePolicy::switchPolicy(bool lruEnabled)
{
    mode = lruEnabled ? MODE_LRU : MODE_RANDOM;
}