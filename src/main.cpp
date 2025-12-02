#include <dlfcn.h>
#include <link.h>
#include <span>
#include <string>
#include "main.h"
#include <libhat.hpp>

extern "C" [[gnu::visibility("default")]] void mod_preinit() {}
extern "C" [[gnu::visibility("default")]] void mod_init()
{
    void *mcLib = dlopen("libminecraftpe.so", 0);
    if (!mcLib)
    {
        printf("[ShulkerPreview] failed to open libminecraftpe.so\n");
        return;
    }

    std::span<std::byte> range1, range2;
    auto callback = [&](const dl_phdr_info &info)
    {
        if (auto h = dlopen(info.dlpi_name, RTLD_NOLOAD); dlclose(h), h != mcLib)
            return 0;
        range1 = {reinterpret_cast<std::byte *>(info.dlpi_addr + info.dlpi_phdr[1].p_vaddr), info.dlpi_phdr[1].p_memsz};
        range2 = {reinterpret_cast<std::byte *>(info.dlpi_addr + info.dlpi_phdr[2].p_vaddr), info.dlpi_phdr[2].p_memsz};
        return 1;
    };
    dl_iterate_phdr([](dl_phdr_info *info, size_t, void *data)
                    { return (*static_cast<decltype(callback) *>(data))(*info); }, &callback);

    // ShulkerBoxBlockItem
    auto ZTS19ShulkerBoxBlockItem = hat::find_pattern(range1, hat::object_to_signature("19ShulkerBoxBlockItem")).get();
    auto _ZTI19ShulkerBoxBlockItem = hat::find_pattern(range2, hat::object_to_signature(ZTS19ShulkerBoxBlockItem)).get() - sizeof(void *);
    auto _ZTV19ShulkerBoxBlockItem = hat::find_pattern(range2, hat::object_to_signature(_ZTI19ShulkerBoxBlockItem)).get() + sizeof(void *);
    void **vtshulk53 = reinterpret_cast<void **>(_ZTV19ShulkerBoxBlockItem);
    // append slot 53
    ShulkerBoxBlockItem_appendFormattedHovertext_orig =
        reinterpret_cast<Shulker_appendHover_t>(vtshulk53[53]);
    vtshulk53[53] = reinterpret_cast<void *>(&ShulkerBoxBlockItem_appendFormattedHovertext_hook);

    // HovertextRenderer
    auto _ZTS17HoverTextRenderer = hat::find_pattern(range1, hat::object_to_signature("17HoverTextRenderer")).get();
    auto _ZTI17HoverTextRenderer = hat::find_pattern(range2, hat::object_to_signature(_ZTS17HoverTextRenderer)).get() - sizeof(void *);
    auto _ZTV17HoverTextRenderer = hat::find_pattern(range2, hat::object_to_signature(_ZTI17HoverTextRenderer)).get() + sizeof(void *);
    // slot17
    void **vtHR = reinterpret_cast<void **>(_ZTV17HoverTextRenderer);
    HoverRenderer_renderHoverBox_orig =
        reinterpret_cast<RenderHoverBoxFn>(vtHR[17]);
    vtHR[17] = reinterpret_cast<void *>(&HoverRenderer_renderHoverBox_hook);
}