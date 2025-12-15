#pragma once
#include <string>
#include <cstddef>
#include "item/item.h"
#include "util/xhelper.h"
//ts's a test, need to actually use Item correct 
class Level;
class ItemStackBase;

using WItem_appendHover_t =
    void (*)(const Item*, const ItemStackBase&, Level&, std::string&, uint8_t);

inline WItem_appendHover_t WItem_appendFormattedHovertext_orig = nullptr;

inline void WItem_appendFormattedHovertext_hook(
    const Item* self,
    const ItemStackBase& stack,
    Level& level,
    std::string& out,
    uint8_t showCategory
) {
    WItem_appendFormattedHovertext_orig(self, stack, level, out, showCategory);

    int max = self->getMaxDamage();
    if (max <= 0)
        return;

    short dmg = ItemStackBase_getDamageValue(
        const_cast<ItemStackBase*>(&stack)
    );

    int current = max - dmg;
    if (current < 0)
        current = 0;

    out.append("\n§7Durability: ");
    out.append(std::to_string(current));
    out.append(" / ");
    out.append(std::to_string(max));
}
