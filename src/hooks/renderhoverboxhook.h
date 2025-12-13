#pragma once
#include "ui/hoverrenderer.h"
#include "shulkerenderer/shulkerrenderer.h"
#include "shulkerenderer/colors.h"
#include "util/keybinds.h"
#include <string>

static bool sPreviewEnabled = false;
static bool sWasHDown = false;

using RenderHoverBoxFn =
    void (*)(void*, MinecraftUIRenderContext*, void*, void*, float);

RenderHoverBoxFn HoverRenderer_renderHoverBox_orig = nullptr;

void HoverRenderer_renderHoverBox_hook(
    void* selfPtr,
    MinecraftUIRenderContext* ctx,
    void* client,
    void* aabb,
    float someFloat)
{
    HoverRenderer* self = reinterpret_cast<HoverRenderer*>(selfPtr);
    const std::string& text = self->mFilteredContent;

    HoverRenderer_renderHoverBox_orig(selfPtr, ctx, client, aabb, someFloat);

    if (text.empty() || !ctx){
        sWasHDown = false;
        return;
    }

    if (text.find("\xC2\xA7v") == std::string::npos){
        sWasHDown = false;
        return;
    }

    char colorCode = '0';
    bool found = false;

    for (size_t i = 0; i + 4 <= text.size(); ++i){
        if ((unsigned char)text[i]     == 0xC2 &&
            (unsigned char)text[i + 1] == 0xA7 &&
            text[i + 2] == '#'){
            colorCode = text[i + 3];
            found = true;
            break;
        }
    }

    if (!found)
        return;

    if (!gSP_KeyDown && sWasHDown){
        sPreviewEnabled = !sPreviewEnabled;
    }
    sWasHDown = gSP_KeyDown;

    if (!sPreviewEnabled)
        return;

    float px = self->mCursorX + self->mOffsetX + 2.0f;
    float py = self->mCursorY + self->mOffsetY + self->mBoxHeight + 2.0f;

    ShulkerRenderer::render(ctx, px, py, colorCode);
}
