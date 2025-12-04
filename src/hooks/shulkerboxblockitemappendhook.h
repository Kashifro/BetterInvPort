#pragma once
#include "item/itemstackbase.h"
#include "shulkerenderer/colors.h"
#include <string>
#include <cstdio>

extern bool gSP_ToggleMode;

class ShulkerBoxBlockItem;

static inline std::string extractShulkerColorName(const std::string &dbg)
{
    const std::string key = "mBlock = name: minecraft:";
    auto pos = dbg.find(key);
    if (pos == std::string::npos)
        return "undyed";

    pos += key.size();

    auto end = dbg.find(',', pos);
    if (end == std::string::npos)
        end = dbg.size();

    std::string full = dbg.substr(pos, end - pos);
    const std::string suffix = "_shulker_box";

    if (full.size() > suffix.size() &&
        full.rfind(suffix) == full.size() - suffix.size())
    {
        full.resize(full.size() - suffix.size());
    }

    if (full.empty())
        full = "undyed";

    return full;
}

using Shulker_appendHover_t =
    void (*)(void *, ItemStackBase *, void *, std::string &, bool);

Shulker_appendHover_t ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem *self,
    ItemStackBase *stack,
    void *level,
    std::string &out,
    bool flag)
{
    if (ShulkerBoxBlockItem_appendFormattedHovertext_orig)
        ShulkerBoxBlockItem_appendFormattedHovertext_orig(self, stack, level, out, flag);

    if (!stack)
        return;
    std::string dbg = stack->toDebugString();
    std::string colorName = extractShulkerColorName(dbg);
    char colorCode = getShulkerColorCodeFromName(colorName);

    bool hasNbt = (stack->mUserData != nullptr);

    out.append("\n");
    out.append(hasNbt ? "Contains items" : "Empty Shulker Box");
    out.append("\n§7Press §eH§7 to toggle preview");
    out.append("\n");
    out.append("\xC2\xA7#");
    out.push_back(colorCode);
    out.append("\xC2\xA7v");
}
