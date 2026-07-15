#include "RandomPolicy.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

RandomPolicy::RandomPolicy()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void RandomPolicy::access(int index)
{
    // No action needed
}

void RandomPolicy::insert(int index)
{
    blocks.push_back(index);
}

int RandomPolicy::chooseVictim()
{
    if (blocks.empty())
        return -1;

    int pos = std::rand() % blocks.size();
    int victim = blocks[pos];

    blocks.erase(blocks.begin() + pos);

    return victim;
}

const char* RandomPolicy::name() const
{
    return "Random";
}