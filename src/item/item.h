#pragma once

#include <string>
#include <cstdint>

class CompoundTag;
class ItemStack;
class ItemStackBase;
class Level;

class Item {
public:
    class Tier {};
    class ScopedCreativeGroup {};
    
    static uintptr_t vtbl;  

    short mMaxDamage;

    Item(const std::string& identifier, short numId);

    static void constructor(Item* self, const std::string& identifier, short numId);

    virtual ~Item();
    virtual void vfunc1() = 0;
    virtual void vfunc2() = 0;
    virtual void vfunc3() = 0;
    virtual void vfunc4() = 0;
    virtual void vfunc5() = 0;
    virtual void vfunc6() = 0;
    virtual void vfunc7() = 0;
    virtual void vfunc8() = 0;
    virtual void vfunc9() = 0;
    virtual void vfunc10() = 0;
    virtual void vfunc11() = 0;
    virtual void vfunc12() = 0;
    virtual void vfunc13() = 0;
    virtual void vfunc14() = 0;
    virtual void vfunc15() = 0;
    virtual void vfunc16() = 0;
    virtual void vfunc17() = 0;
    virtual void vfunc18() = 0;
    virtual void vfunc19() = 0;
    virtual void vfunc20() = 0;
    virtual void vfunc21() = 0;
    virtual void vfunc22() = 0;
    virtual void vfunc23() = 0;
    virtual void vfunc24() = 0;
    virtual void vfunc25() = 0;
    virtual void vfunc26() = 0;
    virtual void vfunc27() = 0;
    virtual void vfunc28() = 0;
    virtual void vfunc29() = 0;
    virtual void vfunc30() = 0;
    virtual void vfunc31() = 0;
    virtual void vfunc32() = 0;
    virtual void vfunc33() = 0;
    virtual void vfunc34() = 0;
    virtual void vfunc35() = 0;
    virtual short getMaxDamage() const; // index 36
    virtual void vfunc37() = 0;
    virtual void vfunc38() = 0;
    virtual void vfunc39() = 0;
    virtual void vfunc40() = 0;
    virtual void vfunc41() = 0;
    virtual void vfunc42() = 0;
    virtual void vfunc43() = 0;
    virtual void vfunc44() = 0;
    virtual void vfunc45() = 0;
    virtual void vfunc46() = 0;
    virtual void vfunc47() = 0;
    virtual void vfunc48() = 0;
    virtual void vfunc49() = 0;
    virtual void vfunc50() = 0;
    virtual void vfunc51() = 0;
    virtual void vfunc52() = 0;
    virtual void appendFormattedHovertext(const ItemStackBase& stack, Level& level, std::string& outText, bool showCategory) const;
    // virtual short getDamageValue(const CompoundTag* userData) const;
};
//prolly not using this :( i do realise i could've used offsets 