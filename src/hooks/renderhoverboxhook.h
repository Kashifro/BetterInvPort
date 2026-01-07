#pragma once
#include "ui/hoverrenderer.h"
#include "shulkerenderer/shulkerrenderer.h"
#include "util/keybinds.h"
#include <string>

static bool sPreviewEnabled = false;
static bool sWasHDown = false;

using RenderHoverBoxFn = void (*)(void*, MinecraftUIRenderContext*, void*, void*, float);

inline RenderHoverBoxFn HoverRenderer_renderHoverBox_orig = nullptr;

static inline int hex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

inline void HoverRenderer_renderHoverBox_hook(
    void* selfPtr,
    MinecraftUIRenderContext* ctx,
    void* client,
    void* aabb,
    float someFloat)
{
    HoverRenderer* self = reinterpret_cast<HoverRenderer*>(selfPtr);

    HoverRenderer_renderHoverBox_orig(selfPtr, ctx, client, aabb, someFloat);

    if (!ctx){
        sWasHDown = false;
        return;
    }

    if (!gSP_KeyDown && sWasHDown)
        sPreviewEnabled = !sPreviewEnabled;
    sWasHDown = gSP_KeyDown;

    if (!sPreviewEnabled)
        return;

    const std::string& text = self->mFilteredContent;

    if (text.find("\xC2\xA7v") == std::string::npos)
        return;

    if (text.size() < 6)
        return;

    char hi = text[2];
    char lo = text[5];
    int index = (hex(hi) << 4) | hex(lo);
    index &= (SHULKER_CACHE_SIZE - 1);

    if (index < 0 || index >= SHULKER_CACHE_SIZE)
        return;

    size_t colorPos = text.find("\xC2\xA7#", 0);
    if (colorPos == std::string::npos || colorPos + 3 >= text.size())
        return;

    char colorCode = text[colorPos + 3];

    float px = self->mCursorX + self->mOffsetX + 2.0f;
    float py = self->mCursorY + self->mOffsetY + self->mBoxHeight + 2.0f;

    ShulkerRenderer::render(ctx, px, py, index, colorCode);
}
