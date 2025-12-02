#pragma once
#include "ui/minecraftuirendercontext.h"
#include "ui/hoverrenderer.h"
#include "shulkerenderer/shulkerrenderer.h"
#include "shulkerenderer/colors.h"
#include <string>

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

    if (text.empty() || !ctx)
        return;

    if (text.find("\xC2\xA7v") == std::string::npos)
        return;

    char colorCode = '0';
    bool found = false;

    for (size_t i = 0; i + 4 <= text.size(); ++i){
        if ((unsigned char)text[i]     == 0xC2 &&
            (unsigned char)text[i + 1] == 0xA7 &&
            text[i + 2] == '#' ){
            colorCode = text[i + 3];
            found = true;
            break;
        }
    }

    if (!found)
        return;

    mce::Color accent = getShulkerTint(colorCode);

    float x0 = self->mCursorX + self->mOffsetX;
    float y0 = self->mCursorY + self->mOffsetY;
    float x1 = x0 + self->mBoxWidth;
    float y1 = y0 + self->mBoxHeight;

    const float th = 2.0f;

    RectangleArea top { x0, x1,      y0,      y0 + th };
    RectangleArea bot { x0, x1,      y1 - th, y1     };
    RectangleArea lef { x0, x0 + th, y0,      y1     };
    RectangleArea rig { x1 - th, x1, y0,      y1     };

    ctx->fillRectangle(top, accent, accent.a);
    ctx->fillRectangle(bot, accent, accent.a);
    ctx->fillRectangle(lef, accent, accent.a);
    ctx->fillRectangle(rig, accent, accent.a);

    float px = x0;
    float py = y1 + 4.0f;

    ShulkerRenderer::render(ctx, px, py, colorCode);
}
