#pragma once
#include <string>
#include <cstdint>

#pragma pack(push, 4)
struct NinesliceInfo
{
    float left;
    float right;
    float top;
    float bottom;
};
#pragma pack(pop)

namespace mce
{
    struct Color;
    class TexturePtr;
}

namespace ui
{
    enum class TextAlignment : std::uint8_t;
}

#pragma pack(push, 4)
struct RectangleArea
{
    float _x0;
    float _x1;
    float _y0;
    float _y1;
};
#pragma pack(pop)

namespace mce
{
    struct Color
    {
        float r, g, b, a;
    };
}

namespace mce {
class TexturePtr {
public:
    void* texture;           
    void* resourceLocation;  
};
}

struct TextMeasureData;
struct CaretMeasureData;
struct ComponentRenderBatch;
class Font;
class CustomRenderComponent;
class ResourceLocation;
class MinecraftUIMeasureStrategy;

class MinecraftUIRenderContext
{
public:
    void *vtable;

    virtual ~MinecraftUIRenderContext(); // 0
    virtual float getLineLength(         // 1
        Font &font,
        std::string const &text,
        float fontSize,
        bool showColorSymbols) const;

    virtual float getTextAlpha() const;     // 2
    virtual void setTextAlpha(float alpha); // 3

    virtual void drawDebugText( // 4
        RectangleArea const &area,
        std::string const &text,
        mce::Color const &color,
        float scale,
        ui::TextAlignment alignment,
        TextMeasureData const &measure,
        CaretMeasureData const &caret);

    virtual void drawText( // 5
        Font &font,
        RectangleArea const &area,
        std::string const &text,
        mce::Color const &color,
        float scale,
        ui::TextAlignment alignment,
        TextMeasureData const &measure,
        CaretMeasureData const &caret);

    virtual void flushText(float deltaTime); // 6
    virtual void drawImage(                  // 7
        mce::TexturePtr const &tex,
        void const *pos,  // glm::vec2 const&
        void const *size, // glm::vec2 const&
        void const *uv0,  // glm::vec2 const&
        void const *uv1   // glm::vec2 const&
    );

    virtual void drawNineslice(
        mce::TexturePtr const &tex,
        NinesliceInfo const &nine);

    virtual void flushImages( // 9
        mce::Color const &col,
        float alpha,
        class HashedString const &materialName);

    virtual void beginSharedMeshBatch(ComponentRenderBatch &batch); // 10
    virtual void endSharedMeshBatch(ComponentRenderBatch &batch);   // 11

    virtual void _unk12(); // 12
    virtual void _unk13(); // 13

    virtual void drawRectangle( // 14
        RectangleArea const &area,
        mce::Color const &color,
        float alpha,
        int thickness);

    virtual void fillRectangle( // 15
        RectangleArea const &area,
        mce::Color const &color,
        float alpha);

    virtual void increaseStencilRef();                            // 16
    virtual void decreaseStencilRef();                            // 17
    virtual void resetStencilRef();                               // 18
    virtual void fillRectangleStencil(RectangleArea const &area); // 19
    virtual void enableScissorTest(RectangleArea const &area);    // 20
    virtual void disableScissorTest();                            // 21
    virtual void setClippingRectangle(RectangleArea const &area); // 22
    virtual void setFullClippingRectangle();                      // 23
    virtual void saveCurrentClippingRectangle();                  // 24
    virtual void restoreSavedClippingRectangle();                 // 25
    virtual RectangleArea getFullClippingRectangle() const;       // 26

    virtual void _unk27(); // 27

    virtual void renderCustom( // 28
        CustomRenderComponent *comp,
        int pass,
        RectangleArea &aabb);

    virtual void _unk29(); // 29
    virtual void _unk30(); // 30
    virtual void _unk31(); // 31
    virtual void _unk32(); // 32
    virtual void _unk33(); // 33
    virtual void _unk34(); // 34

    virtual void touchTexture(ResourceLocation const &);      // 35
    virtual MinecraftUIMeasureStrategy *getMeasureStrategy(); // 36

    virtual void snapImageSizeToGrid(void *sizeVec); // 37

    virtual void _unk38();                                    // 38
    virtual void notifyImageEstimate(std::uint64_t estimate); // 39
};
