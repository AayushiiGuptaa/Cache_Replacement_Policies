#ifndef REPLACEMENT_POLICY_H
#define REPLACEMENT_POLICY_H

#include <vector>

class ReplacementPolicy {
public:
    virtual ~ReplacementPolicy() {}

    
    virtual void access(int index) = 0;

    
    virtual int chooseVictim() = 0;

    
    virtual void insert(int index) = 0;

   
    virtual const char* name() const = 0;
};

#endif