#include "shulkerrenderer.h"
#include "shulkerenderer/colors.h"

bool ShulkerRenderer::sHasPanelTex = false;
mce::TexturePtr ShulkerRenderer::sPanelTex{};
uiutil::NineSlice ShulkerRenderer::sPanelSlice(256.0f, 256.0f, 4.0f, 4.0f);

void ShulkerRenderer::setPanelTexture(mce::TexturePtr const &tex)
{
    sPanelTex = tex;
    sHasPanelTex = true;
}

void ShulkerRenderer::render(
    MinecraftUIRenderContext *ctx,
    float x,
    float y,
    char colorCode){
    if (!ctx)
        return;

    const float slotSize = 18.0f;
    const float thin = 1.0f;
    const float width = slotSize * 9.0f;
    const float height = slotSize * 3.0f;

    RectangleArea panel;
    panel._x0 = x - 4.0f;
    panel._x1 = x + width + 4.0f;
    panel._y0 = y - 4.0f;
    panel._y1 = y + height + 4.0f;

    mce::Color tint = getShulkerTint(colorCode);

    // var
    mce::Color borderCol = tint;
    mce::Color innerCol{
        tint.r * 0.25f,
        tint.g * 0.25f,
        tint.b * 0.25f,
        0.95f};

    mce::Color slotBorder = tint;
    mce::Color slotFill{
        tint.r * 0.30f,
        tint.g * 0.30f,
        tint.b * 0.30f,
        1.0f};

    // bg
    if (!sHasPanelTex){
        ctx->fillRectangle(panel, borderCol, borderCol.a);

        RectangleArea inner;
        inner._x0 = panel._x0 + thin;
        inner._x1 = panel._x1 - thin;
        inner._y0 = panel._y0 + thin;
        inner._y1 = panel._y1 - thin;

        ctx->fillRectangle(inner, innerCol, innerCol.a);
    }
    else{
        mce::Color tintApply = tint;
        sPanelSlice.draw(ctx, sPanelTex, panel, &tintApply);
    }

    // bevel highlight
    {
        RectangleArea hl{panel._x0, panel._x1, panel._y0, panel._y0 + thin};
        mce::Color c{1, 1, 1, 0.22f};
        ctx->fillRectangle(hl, c, c.a);
    }

    // bevel shadow
    {
        RectangleArea sh{panel._x0, panel._x1, panel._y1 - thin, panel._y1};
        mce::Color c{0, 0, 0, 0.35f};
        ctx->fillRectangle(sh, c, c.a);
    }
    // slots
    for (int r = 0; r < 3; ++r){
        for (int c = 0; c < 9; ++c){
            float sx = x + c * slotSize;
            float sy = y + r * slotSize;

            RectangleArea slot{sx, sx + slotSize, sy, sy + slotSize};
            ctx->fillRectangle(slot, slotBorder, slotBorder.a);

            RectangleArea inner{
                slot._x0 + thin,
                slot._x1 - thin,
                slot._y0 + thin,
                slot._y1 - thin};

            ctx->fillRectangle(inner, slotFill, slotFill.a);

            // highlight
            {
                RectangleArea hl{inner._x0, inner._x1, inner._y0, inner._y0 + thin};
                mce::Color c2{1, 1, 1, 0.18f};
                ctx->fillRectangle(hl, c2, c2.a);
            }

            // shadow
            {
                RectangleArea sh2{inner._x0, inner._x1, inner._y1 - thin, inner._y1};
                mce::Color c3{0, 0, 0, 0.28f};
                ctx->fillRectangle(sh2, c3, c3.a);
            }
        }
    }
}
