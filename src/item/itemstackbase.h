#pragma once
#include <cstdint>
#include <string>
#include "nbt/compoundtag.h"

class ItemStackBase {
public:
    void*        mItem;       // 0x08 (WeakPtr<Item>, treated as opaque)
    CompoundTag* mUserData;   // 0x10

    // we don't need the rest of the fields for now; leave them opaque

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
