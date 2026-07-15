#include "LRUPolicy.h"

void LRUPolicy::access(int index)
{
    auto it = position.find(index);

    if (it == position.end())
        return;

    order.erase(it->second);
    order.push_front(index);
    position[index] = order.begin();
}

void LRUPolicy::insert(int index)
{
    auto it = position.find(index);

    // Remove existing occurrence if already present
    if (it != position.end())
    {
        order.erase(it->second);
        position.erase(it);
    }

    order.push_front(index);
    position[index] = order.begin();
}

int LRUPolicy::chooseVictim()
{
    if (order.empty())
        return -1;

    int victim = order.back();
    order.pop_back();
    position.erase(victim);

    return victim;
}

const char* LRUPolicy::name() const
{
    return "LRU";
}