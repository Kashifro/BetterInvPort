#pragma once
#include <cstdint>
#include <string>

class MinecraftUIRenderContext;
class Font;
struct RectangleArea;
struct TextMeasureData;
struct CaretMeasureData;

namespace mce { struct Color; }
namespace ui { enum class TextAlignment : uint8_t; }

// live UI context + font for this frame
inline MinecraftUIRenderContext* ActiveUIContext = nullptr;
inline Font* ActiveUIFont = nullptr;

using MinecraftUIRenderContext_drawText_t = void(*)(
        MinecraftUIRenderContext*,
        Font&,
        const RectangleArea&,
        const std::string&,
        const mce::Color&,
        ui::TextAlignment,
        float,
        const TextMeasureData&,
        const CaretMeasureData&);

inline MinecraftUIRenderContext_drawText_t MinecraftUIRenderContext_drawText_orig = nullptr;

inline void MinecraftUIRenderContext_drawText_hook(
    MinecraftUIRenderContext* self,
    Font& font,
    const RectangleArea& rect,
    const std::string& text,
    const mce::Color& color,
    ui::TextAlignment align,
    float alpha,
    const TextMeasureData& tmd,
    const CaretMeasureData& cmd
) {
    ActiveUIContext = self;
    ActiveUIFont   = &font;

    MinecraftUIRenderContext_drawText_orig(
        self, font, rect, text, color, align, alpha, tmd, cmd
    );
}
//this is basically stealing the drawtext