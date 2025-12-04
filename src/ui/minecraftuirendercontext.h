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

namespace mce
{
    class TexturePtr
    {
    public:
        void *texture;
        void *resourceLocation;
    };
}

struct TextMeasureData;
struct CaretMeasureData;
struct ComponentRenderBatch;
class Font;
class CustomRenderComponent;
class ResourceLocation;
class MinecraftUIMeasureStrategy;
class HashedString;

class MinecraftUIRenderContext
{
public:
    void *vtable; // shouldn't be here but eh for the index ig
    virtual ~MinecraftUIRenderContext();

    virtual float getLineLength(
        Font &font, std::string const &, float, bool) const;

    virtual float getTextAlpha() const;
    virtual void setTextAlpha(float);
    virtual void drawDebugText(
        RectangleArea const &, std::string const &, mce::Color const &,
        float, ui::TextAlignment,
        TextMeasureData const &, CaretMeasureData const &);

    virtual void drawText(
        Font &, RectangleArea const &, std::string const &,
        mce::Color const &, float, ui::TextAlignment,
        TextMeasureData const &, CaretMeasureData const &);

    virtual void flushText(float);
    virtual void drawImage(
        mce::TexturePtr const &,
        void const *pos, 
        void const *size,
        void const *uv0, 
        void const *uv1);

    virtual void drawNineslice(
        mce::TexturePtr const &, NinesliceInfo const &);

    virtual void flushImages(
        mce::Color const &, float, HashedString const &);

    virtual void beginSharedMeshBatch(
        ComponentRenderBatch &);

    virtual void endSharedMeshBatch(
        ComponentRenderBatch &);

    virtual void _unk13();
    virtual void _unk14();

    virtual void drawRectangle(
        RectangleArea const &, mce::Color const &, float, int);

    virtual void fillRectangle(
        RectangleArea const &, mce::Color const &, float);

    virtual void increaseStencilRef();
    virtual void decreaseStencilRef();
    virtual void resetStencilRef();
    virtual void fillRectangleStencil(RectangleArea const &);
    virtual void enableScissorTest(RectangleArea const &);
    virtual void disableScissorTest();
    virtual void setClippingRectangle(RectangleArea const &);
    virtual void setFullClippingRectangle();
    virtual void saveCurrentClippingRectangle();
    virtual void restoreSavedClippingRectangle();
    virtual RectangleArea getFullClippingRectangle() const;
    virtual void _unk28();

    virtual void renderCustom(
        CustomRenderComponent *, int, RectangleArea &);

    virtual void cleanup();
    virtual void _unk31();

    virtual mce::TexturePtr getTexture(
        ResourceLocation const &, bool);

    virtual void _unk33();
    virtual void _unk34();
    virtual void _unk35();
    virtual void touchTexture(ResourceLocation const &);

    virtual MinecraftUIMeasureStrategy *getMeasureStrategy();
    virtual void snapImageSizeToGrid(void *sizeVec);
    virtual void _unk39();
    virtual void notifyImageEstimate(std::uint64_t);
};