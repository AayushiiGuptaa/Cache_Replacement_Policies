#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <memory>
#include "ReplacementPolicy.h"

struct CacheLine
{
    bool valid;
    unsigned long tag;

    CacheLine() : valid(false), tag(0) {}
};

class Cache
{
private:
    int cacheSize;
    int blockSize;
    int numBlocks;

    std::vector<CacheLine> lines;

    std::unique_ptr<ReplacementPolicy> policy;

    int hits;
    int misses;

public:
    Cache(int cacheSize,
          int blockSize,
          ReplacementPolicy* replacementPolicy);

    bool access(unsigned long address);

    double getHitRate() const;

    int getHits() const;

    int getMisses() const;

    void reset();
};

#endif