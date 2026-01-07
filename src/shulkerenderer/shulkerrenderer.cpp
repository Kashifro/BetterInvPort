#include "shulkerrenderer.h"

void ShulkerRenderer::render(
    MinecraftUIRenderContext* ctx,
    float x,
    float y,
    int index,
    char colorCode
) {
    if (!ctx || !ActiveUIContext || !ActiveUIFont)
        return;

    constexpr int   COLS = 9;
    constexpr int   ROWS = 3;
    constexpr float SLOT = 18.0f;
    constexpr float DRAW = 17.5f;
    constexpr float PAD  = 3.0f;
    constexpr float BEV  = 0.25f;

    mce::Color tint = getShulkerTint(colorCode);
    mce::Color panelFill { tint.r, tint.g, tint.b, 0.95f };
    mce::Color slotBorder = tint;
    mce::Color slotFill {
        tint.r * 0.30f,
        tint.g * 0.30f,
        tint.b * 0.30f,
        1.0f
    };

    RectangleArea panel {
        x,
        x + COLS * SLOT + PAD * 2.0f,
        y,
        y + ROWS * SLOT + PAD * 2.0f
    };
    ctx->fillRectangle(panel, panelFill, panelFill.a);

    float sx0 = x + PAD;
    float sy0 = y + PAD;

    Font& font = *ActiveUIFont;

    TextMeasureData tmd{};
    tmd.fontSize = 1.0f;
    tmd.renderShadow = false;

    CaretMeasureData cmd{};
    cmd.position = 0;
    cmd.shouldRender = false;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int slotIndex = r * COLS + c;
            ShulkerSlotCache& sc = gShulkerCache[index][slotIndex];

            float sx = sx0 + c * SLOT;
            float sy = sy0 + r * SLOT;

            RectangleArea slot { sx, sx + DRAW, sy, sy + DRAW };
            ctx->fillRectangle(slot, slotBorder, slotBorder.a);

            RectangleArea inner {
                slot._x0 + BEV,
                slot._x1 - BEV,
                slot._y0 + BEV,
                slot._y1 - BEV
            };
            ctx->fillRectangle(inner, slotFill, slotFill.a);

            if (!sc.valid || sc.count <= 1)
                continue;

            char buf[8];
            snprintf(buf, sizeof(buf), "%u", sc.count);

            //anchor BotRt
            float anchorX = sx + DRAW - 0.5f;
            float anchorY = sy + DRAW - 1.5f;

            
            float textW = ActiveUIContext->getLineLength(
                font,
                buf,
                tmd.fontSize,
                false
            );

            //heighttext
            float textH = 6.0f;

            RectangleArea shadow {
                anchorX - textW + 1.0f,
                anchorX + 1.0f,
                anchorY - textH + 1.0f,
                anchorY + 1.0f
            };

            RectangleArea text {
                anchorX - textW,
                anchorX,
                anchorY - textH,
                anchorY
            };

            // shadow
            ActiveUIContext->drawText(
                font,
                shadow,
                buf,
                mce::Color{0, 0, 0, 0.75f},
                1.0f,
                ui::TextAlignment::Right,
                tmd,
                cmd
            );

            // text
            ActiveUIContext->drawText(
                font,
                text,
                buf,
                mce::Color{1, 1, 1, 1},
                1.0f,
                ui::TextAlignment::Right,
                tmd,
                cmd
            );

        }
    }

    ctx->flushText(0.0f);
}
