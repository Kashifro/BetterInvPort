#pragma once
#include <cstdint>
#include <string>

class CompoundTag;

class ItemStackBase {
public:
    void*        mItem;       
    CompoundTag* mUserData; 

    ItemStackBase();
    ItemStackBase(const ItemStackBase&);
    ItemStackBase& operator=(const ItemStackBase&);

    virtual ~ItemStackBase();
    virtual void _unkFunc1();
    virtual void _unkFunc2();
    virtual void _unkFunc3();
    virtual void _unkFunc4();
    virtual std::string toString() const;
    virtual std::string toDebugString() const;
};
