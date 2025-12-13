#pragma once
#include "item/itemstackbase.h"
#include "shulkerenderer/colors.h"
#include "nbt/nbt.h"
#include <string>
#include <cstddef>

extern bool gSP_ToggleMode;

class ShulkerBoxBlockItem;

static inline uint8_t getTagId(void* tag){
    auto vtbl = *reinterpret_cast<void***>(tag);
    auto fn   = reinterpret_cast<uint8_t (*)(void*)>(vtbl[6]);
    return fn(tag);
}

static inline std::string extractShulkerColorName(const std::string& dbg){
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
        full.resize(full.size() - suffix.size());

    if (full.empty())
        full = "undyed";

    return full;
}

using Shulker_appendHover_t =
    void (*)(void*, ItemStackBase*, void*, std::string&, bool);

inline Shulker_appendHover_t
    ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

inline void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem* self,
    ItemStackBase* stack,
    void* level,
    std::string& out,
    bool flag)
{
    if (ShulkerBoxBlockItem_appendFormattedHovertext_orig)
        ShulkerBoxBlockItem_appendFormattedHovertext_orig(
            self, stack, level, out, flag);

    if (!stack || !stack->mUserData)
        return;

    if (!CompoundTag_getList ||
        !ListTag_get ||
        !ListTag_size ||
        !ItemStackBase_ctor ||
        !ItemStackBase_loadItem ||
        !ItemStackBase_getName)
        return;

    void* list = CompoundTag_getList(stack->mUserData, "Items", 5);
    if (!list)
        return;

    constexpr int MAX_PREVIEW = 10;

    int size   = ListTag_size(list);
    int shown  = 0;
    int hidden = 0;

    for (int i = 0; i < size; ++i) {
        void* tag = ListTag_get(list, i);
        if (!tag || getTagId(tag) != 10)
            continue;

        if (shown >= MAX_PREVIEW) {
            ++hidden;
            continue;
        }

        alignas(16) std::byte buf[0x100]{};
        auto* loaded = reinterpret_cast<ItemStackBase*>(buf);

        ItemStackBase_ctor(loaded);
        ItemStackBase_loadItem(loaded, tag);

        std::string name;
        ItemStackBase_getName(&name, loaded);

        uint8_t count =
            *reinterpret_cast<uint8_t*>(
                reinterpret_cast<char*>(loaded) + 34);

        out += "\n§a";
        out += name.empty() ? "Item" : name;
        out += " x";
        out += std::to_string(count);

        ++shown;
    }

    if (hidden > 0) {
        out += "\n§7and ";
        out += std::to_string(hidden);
        out += " more…";
    }

    //marker
    out += "\n§7Press §eH§7 to toggle preview";
    out += "\xC2\xA7#";
    out.push_back(
        getShulkerColorCodeFromName(
            extractShulkerColorName(stack->toDebugString())));
    out += "\xC2\xA7v";
}
