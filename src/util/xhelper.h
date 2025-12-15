#pragma once
#include <cstddef>
#include <cstring>
#include <string>
//why?
class ItemStackBase;
class BaseActorRenderContext;

using CompoundTag_getList_t =
    void* (*)(void* compound, const char* key, size_t len);
extern CompoundTag_getList_t CompoundTag_getList;

using CompoundTag_contains_t =
    bool (*)(void* compound, const char* key, size_t len);
extern CompoundTag_contains_t CompoundTag_contains;

using ListTag_get_t =
    void* (*)(void* list, int index);
extern ListTag_get_t ListTag_get;

using ItemStackBase_loadItem_t =
    void (*)(void* stack, void* compound);
extern ItemStackBase_loadItem_t ItemStackBase_loadItem;

using ListTag_size_t =
    int (*)(void*);
extern ListTag_size_t ListTag_size;

using ItemStackBase_getName_t =
    std::string* (*)(std::string*, ItemStackBase*);
extern ItemStackBase_getName_t ItemStackBase_getName;

using ItemStackBase_ctor_t = void (*)(ItemStackBase*);
extern ItemStackBase_ctor_t ItemStackBase_ctor;

using ItemStackBase_getDamageValue_t = short (*)(ItemStackBase*);

extern ItemStackBase_getDamageValue_t ItemStackBase_getDamageValue;
