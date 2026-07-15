#include "cache.h"

Cache::Cache(int cacheSize,
             int blockSize,
             ReplacementPolicy* replacementPolicy)
{
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;

    numBlocks = cacheSize / blockSize;

    lines.resize(numBlocks);

    policy.reset(replacementPolicy);

    hits = 0;
    misses = 0;
}

bool Cache::access(unsigned long address)
{
    unsigned long blockAddress = address / blockSize;

    unsigned long tag = blockAddress;

    for (int i = 0; i < numBlocks; i++)
    {
        if (lines[i].valid && lines[i].tag == tag)
        {
            hits++;
            policy->access(i);
            return true;
        }
    }

    misses++;

    int emptyIndex = -1;

    for (int i = 0; i < numBlocks; i++)
    {
        if (!lines[i].valid)
        {
            emptyIndex = i;
            break;
        }
    }

    if (emptyIndex != -1)
    {
        lines[emptyIndex].valid = true;
        lines[emptyIndex].tag = tag;

        policy->insert(emptyIndex);
    }
    else
    {
        int victim = policy->chooseVictim();

        lines[victim].tag = tag;
        lines[victim].valid = true;

        policy->insert(victim);
    }

    return false;
}

double Cache::getHitRate() const
{
    int total = hits + misses;

    if (total == 0)
        return 0.0;

    return static_cast<double>(hits) / total;
}

int Cache::getHits() const
{
    return hits;
}

int Cache::getMisses() const
{
    return misses;
}

void Cache::reset()
{
    hits = 0;
    misses = 0;

    for (auto &line : lines)
    {
        line.valid = false;
    }
}